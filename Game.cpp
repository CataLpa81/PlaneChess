#include"Game.h"
#include<functional>

GameScence GP;

sf::Mutex mutex;
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "CataLpa",sf::Style::Close|sf::Style::Titlebar);

void Game::Initial()
{
	GP = GameScence::BEGIN;
	window.setFramerateLimit(30);
	gm = GameManager::instance();
	gm->dice->addObserver(gm);
	gm->planepool->AddObserver(gm);
	gm->planepool->AddObserver(gm->chessboard);
	
	tbk.loadFromFile("./data/background/sky.jpg");
	spbk.setTexture(tbk);
	ChessBoard::instance()->texture.loadFromFile("./data/Background/chessboard.png");
	ChessBoard::instance()->sprite.setTexture(ChessBoard::instance()->texture);

	ChessBoard_Client::instance()->texture.loadFromFile("./data/Background/chessboard.png");
	ChessBoard_Client::instance()->sprite.setTexture(ChessBoard_Client::instance()->texture);

	bi = BeginInterface::Instance();
	NS1 = NetGame1_Scence::Instance();
	NS2 = NetGame2_Scence::Instance();
	
	AM = AudioManager::Instance();
	AM->SetVolume("BGM", 100);
	AM->Play("BGM");

	gmc = GameManagerClient::instance();
	gmc->dice->addObserver(gmc);
	gmc->planepool->AddObserver(gmc);
	gmc->planepool->AddObserver(ChessBoard_Client::instance());

	static std::thread t2(&Client::Run, c);
	IsClient = true;
}



void Game::Input()
{
	sf::Event event;  //接受窗口事件
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) { // 检测关闭
			window.close();
		}

		switch (GP)
		{
		case GameScence::BEGIN:bi->Input(event);
			break;
		case GameScence::LOCALGAME:gm->GameInputLogic(event);
			break;
		case GameScence::NETGAME1:NS1->Input(event);
			break;
		case GameScence::NETGAME2:NS2->Input(event);
			break;
		case GameScence::NETGAME3:
			break;
		case GameScence::NETGAME:gmc->GameInputLogic(event);
			break;
		default:
			break;
		}
	}
}

void Game::Update()
{
	if (GP == GameScence::LOCALGAME)
		gm->GameUpdateLogic();
	else if (GP == GameScence::NETGAME)
		gmc->GameUpdateLogic();
	
}

void Game::Rander()
{
	window.draw(spbk);
	window.draw(ChessBoard::instance()->sprite);

	switch (GP)
	{
	case GameScence::BEGIN:bi->Render();
		break;
	case GameScence::LOCALGAME:gm->GameRenderLogic();
		break;
	case GameScence::NETGAME1:NetGame1_Scence::Instance()->Render();
		break;
	case GameScence::NETGAME2:NetGame2_Scence::Instance()->Render();
		break;
	case GameScence::NETGAME3:
		break;
	case GameScence::NETGAME:gmc->GameRenderLogic();
		break;
	default:
		break;
	}


	window.display();
}

void Game::Run()
{
	Initial();
	while (window.isOpen())
	{

		Input();
		Update();
		Rander();
	}

	if (!window.isOpen())
	{
		sf::Uint32 exit = EXIT;
		Client::Instance()->socket.send(&exit, sizeof(sf::Uint32));
	}
	
}