#include"Plane.h"
#include"ChessBoard.h"
#include<fstream>




void Plane::Update()
{
	if (state == ONBOARD)
	{
		this->x = chessboard->blocks[pos - 1].x + chessboard->sprite.getPosition().x;
		this->y = chessboard->blocks[pos - 1].y + chessboard->sprite.getPosition().y;
	}
	else if (state == HOME || state == FINAL)
	{
		this->x = home_pos_x;
		this->y = home_pos_y;
	}
	else if (state == READY)
	{
		this->x = ready_pos_x;
		this->y = ready_pos_y;
	}

	this->sprite.setPosition(x, y);
	hitbox = this->sprite.getGlobalBounds();
}



void Plane::move(int step)
{
	if (state == ONBOARD)
	{
		this->pos += step;
		//给观察者发送消息，飞机操作完毕，开始骰子操作
		this->notify(MVCEvent::DICETIME);
	}
	else if (state == HOME&&step == 6)
	{
		state = READY;
		//给观察者发送消息，飞机操作完毕，开始骰子操作
		this->notify(MVCEvent::DICETIME);
	}
	else if (state == READY)
	{
		state = ONBOARD;
		this->pos = step+this->pos_start-1;
		//给观察者发送消息，飞机操作完毕，开始骰子操作
		this->notify(MVCEvent::DICETIME);
	}
}

void Plane::Input(sf::Event& event, int diceNumber)
{
	//当鼠标左键在飞机上释放时
	if (event.type == Event::MouseButtonReleased 
		&& event.mouseButton.button == sf::Mouse::Left
		&& this->hitbox.contains((sf::Vector2f)sf::Mouse::getPosition(window)))
	{
		this->move(diceNumber);
	}
}

bool PlanePoolUnit::JudgeAvailable(int diceNumber)
{
	if (diceNumber == 6)
	{
		return true;
	}
	else
	{
		for (int i = 0;i < 4;i++)
		{
			if (plane[i]->state != Plane::HOME)
				return true;
		}
	}

	return false;
}

void PlanePoolUnit::AddObserver(Observer* observer)
{
	for (int i = 0;i < 4;i++)
	{
		this->plane[i]->addObserver(observer);
	}
}
void PlanePoolUnit::Update()
{
	for (int i = 0;i < 4;i++)
	{
		plane[i]->Update();
	}
}

void PlanePoolUnit::Rander()
{
	for (int i = 0;i < 4;i++)
	{
		plane[i]->Rander();
	}
}

void PlanePoolUnit::Input(sf::Event& event, int diceNumber)
{
	for (int i = 0;i < 4;i++)
	{
		plane[i]->Input(event,diceNumber);
	}
}

RedPlanePool::RedPlanePool()
{
	for (int i = 0;i < 4;i++)this->plane[i] = new RedPlane();
}
BluePlanePool::BluePlanePool()
{
	for (int i = 0;i < 4;i++)this->plane[i] = new BluePlane();
}
YellowPlanePool::YellowPlanePool()
{
	for (int i = 0;i < 4;i++)this->plane[i] = new YellowPlane();
}
GreenPlanePool::GreenPlanePool()
{
	for (int i = 0;i < 4;i++)this->plane[i] = new GreenPlane();
}

void PlanePool::Rander()
{
	redplanepool.Rander();
	blueplanepool.Rander();
	yellowplanepool.Rander();
	greenplanepool.Rander();
};

void PlanePool::Update()
{
	redplanepool.Update();
	blueplanepool.Update();
	yellowplanepool.Update();
	greenplanepool.Update();
}

PlanePool::PlanePool()
{
	//从文件中读取飞机的家的位置
	std::ifstream infile;
	infile.open("homepos.txt");
	for (int i = 0;i < 4;i++)
	{
		int a;
		infile >> a;
		greenplanepool.plane[i]->home_pos_x = a + chessboard->sprite.getPosition().x;
		infile >> a;
		greenplanepool.plane[i]->home_pos_y = a + chessboard->sprite.getPosition().y;
	}
	for (int i = 0;i < 4;i++)
	{
		int a;
		infile >> a;
		redplanepool.plane[i]->home_pos_x = a + chessboard->sprite.getPosition().x;
		infile >> a;
		redplanepool.plane[i]->home_pos_y = a + chessboard->sprite.getPosition().y;
	}
	for (int i = 0;i < 4;i++)
	{
			int a;
			infile >> a;
			yellowplanepool.plane[i]->home_pos_x = a + chessboard->sprite.getPosition().x;
			infile >> a;
			yellowplanepool.plane[i]->home_pos_y = a + chessboard->sprite.getPosition().y;
	}
	for (int i = 0;i < 4;i++)
	{
			int a;
			infile >> a;
			blueplanepool.plane[i]->home_pos_x = a + chessboard->sprite.getPosition().x;
			infile >> a;
			blueplanepool.plane[i]->home_pos_y = a + chessboard->sprite.getPosition().y;
	}

	//从文件中读取飞机的出发位置
	std::ifstream infile_2;
	infile_2.open("readypos.txt");
	int b;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		greenplanepool.plane[i]->ready_pos_x = b + chessboard->sprite.getPosition().x;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		greenplanepool.plane[i]->ready_pos_y = b + chessboard->sprite.getPosition().y;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		redplanepool.plane[i]->ready_pos_x = b + chessboard->sprite.getPosition().x;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		redplanepool.plane[i]->ready_pos_y = b + chessboard->sprite.getPosition().y;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		yellowplanepool.plane[i]->ready_pos_x = b + chessboard->sprite.getPosition().x;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		yellowplanepool.plane[i]->ready_pos_y = b + chessboard->sprite.getPosition().y;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		blueplanepool.plane[i]->ready_pos_x = b + chessboard->sprite.getPosition().x;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		blueplanepool.plane[i]->ready_pos_y = b + chessboard->sprite.getPosition().y;


	currentpool = &redplanepool;
	std::cout << "red turn" << std::endl;

	
	
}

void PlanePool::Input(sf::Event& event,int diceNumber)
{
	currentpool->Input(event,diceNumber);
}

void PlanePool::SwitchToNextTurn()
{
	switch(TURN)
	{
	case RED:
		this->TURN = YELLOW;
		currentpool = &yellowplanepool;
		std::cout << "yellow turn"<< std::endl;
		break;
	case YELLOW:
		this->TURN = BLUE;
		currentpool = &blueplanepool;
		std::cout << "blue turn" << std::endl;
		break;
	case BLUE:
		this->TURN = GREEN;
		currentpool = &greenplanepool;
		std::cout << "green turn" << std::endl;
		break;
	case GREEN:
		this->TURN = RED;
		currentpool = &redplanepool;
		std::cout << "red turn" << std::endl;
		break;
	default:
		break;
	}
}

void PlanePool::AddObserver(Observer* observer)
{
	this->redplanepool.AddObserver(observer);
	this->blueplanepool.AddObserver(observer);
	this->yellowplanepool.AddObserver(observer);
	this->greenplanepool.AddObserver(observer);
}