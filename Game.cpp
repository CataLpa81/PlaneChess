#include"Game.h"

GameScence GP;

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "CataLpa");

void Game::Initial()
{
	GP = GameScence::BEGIN;
	window.setFramerateLimit(30);
	gm = GameManager::instance(Dice::instance(), PlanePool::instance(), ChessBoard::instance());
	gm->dice->addObserver(gm);
	gm->planepool->AddObserver(gm);
	gm->planepool->AddObserver(gm->chessboard);
	tbk.loadFromFile("./data/background/sky.jpg");
	spbk.setTexture(tbk);
	ChessBoard::instance()->texture.loadFromFile("./data/Background/chessboard.png");
	ChessBoard::instance()->sprite.setTexture(ChessBoard::instance()->texture);

	bi = BeginInterface::Instance();
}

void Game::Input()
{
	sf::Event event;  //接受窗口事件
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) { // 检测关闭
			window.close();
		}

		if (GP == GameScence::BEGIN)
			bi->Input(event);

		if (GP == GameScence::GAME)
			gm->GameInputLogic(event);
	}

}

void Game::Update()
{
	if (GP == GameScence::GAME)
		gm->GameUpdateLogic();
}

void Game::Rander()
{
	window.draw(spbk);
	window.draw(ChessBoard::instance()->sprite);

	if (GP == GameScence::BEGIN)
		bi->Render();

	if (GP == GameScence::GAME)
		gm->GameRenderLogic();

	window.display();
}

void Game::Run()
{
	Initial();
	while (1)
	{
		Input();
		Update();
		Rander();
	}
}