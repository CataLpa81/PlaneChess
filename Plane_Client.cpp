#include"Plane_Client.h"
#include"ChessBoard.h"
#include<fstream>
#include<math.h>
#define PI 3.1415926





void Plane_Client::Update()
{
	ChessBoard* cb = ChessBoard::instance();

	if (state == ONBOARD || state == ONFINAL)
	{
		if (lastpos != 0)
		{
			moveUpdate(cb->blocks[lastpos - 1], cb->blocks[pos - 1]);

		}
		else
		{
			block s;
			s.x = this->ready_pos_x;
			s.y = this->ready_pos_y;
			moveUpdate(s, cb->blocks[pos - 1]);
		}
	}
	else if (state == HOME || state == FINAL)
	{
		this->x = home_pos_x;
		this->y = home_pos_y;
		setrotation();
	}


	this->sprite.setPosition(x, y);
	hitbox = this->sprite.getGlobalBounds();
}

void Plane_Client::setrotation()
{

	if (state == ONBOARD)
	{
		if ((pos >= 4 && pos <= 6) || pos == 8 || (pos >= 11 && pos <= 16) || pos == 20 || pos == 22 || pos == 23)
			this->sprite.setRotation(180);
		if ((pos >= 1 && pos <= 3) || pos == 7 || pos == 9 || pos == 10 ||
			(pos >= 43 && pos <= 45) || pos == 47 || (pos >= 50 && pos <= 52))
			this->sprite.setRotation(90);
		if ((pos >= 17 && pos <= 19) || pos == 21 || (pos >= 24 && pos <= 29) ||
			pos == 33 || pos == 35 || pos == 36)
			this->sprite.setRotation(-90);
		if ((pos >= 30 && pos <= 32) || pos == 34 || (pos >= 37 && pos <= 42) || pos == 46
			|| pos == 48 || pos == 49)
			this->sprite.setRotation(0);
	}
	else if (state == ONFINAL)
	{
		this->sprite.setRotation(final_ready_rotation);
	}
	else if (state == READY)
	{
		this->sprite.setRotation(final_ready_rotation);
	}
	else if (state == FINAL)
	{
		this->sprite.setRotation(0);
	}
	else if (state == HOME)
	{
		this->sprite.setRotation(0);
	}

}
void Plane_Client::moveUpdate(block b1, block b2)
{
	if (abs(b2.x - this->x) < 0.001
		&& abs(b2.y - this->y) < float(0.001))
	{
		this->x = b2.x;
		this->y = b2.y;
		//给观察者发送消息，飞机操作完毕，告知棋盘
		this->notify(this, MVCEvent::PLANEMOVE_ONBOARD);

		if (doFly)
			fly();
		if (pos == pos_final_end)
		{
			this->state = FINAL;
			this->sprite.setTexture(finaltexture);
		}
		if (PPU->ready_num != 0)
			PPU->ready_num--;

		setrotation();

		return;
	}

	float dis_x = b2.x - b1.x;
	float dis_y = b2.y - b1.y;
	float alpha = (atan(dis_y / dis_x)) * 180 / PI;
	if (dis_x >= 0)
		this->sprite.setRotation(90 + alpha);
	else if (dis_x < 0)
		this->sprite.setRotation(270 + alpha);

	if (this->x != b2.x
		|| this->y != b2.y)
	{
		float dis_x = b2.x - b1.x;
		float dis_y = b2.y - b1.y;
		this->x += dis_x * movespeed;
		this->y += dis_y * movespeed;
	}


}


void Plane_Client::fly()
{

	//如果踩在第二个多次飞行的格子上
	if (this->stepcount == 18)
	{
		lastpos = pos;
		stepcount += 12;
		pos += 12;
		if (this->pos > 52)
		{
			this->pos -= 52;
		}
	}
	//如果踩在同颜色的格子上
	else if ((stepcount + 2) % 4 == 0 && stepcount < 50 && state == ONBOARD)
	{
		lastpos = pos;
		stepcount += 4;
		pos += 4;
		if (this->pos > 52)
		{
			this->pos -= 52;
		}
	}
	if (stepcount == 18 || (stepcount == 30 && lastpos == 18))
		doFly = true;
	else
		doFly = false;


}
void Plane_Client::move(int step)
{
	if (state == ONBOARD)
	{
		this->lastpos = pos;
		this->stepcount += step;
		this->pos += step;
		if (this->pos > 52)
		{
			this->pos -= 52;
		}
		if (this->stepcount > 50)
		{
			this->state = ONFINAL;
			this->pos = stepcount - 50 + pos_final_start - 1;

		}
		this->notify(this, MVCEvent::DICETIME);

		doFly = true;
	}
	else if (state == HOME && step == 6)
	{
		stepcount = 0;
		state = READY;
		this->x = ready_pos_x;
		this->y = ready_pos_y;

		setrotation();
		//给观察者发送消息，飞机操作完毕，开始骰子操作
		this->notify(this, MVCEvent::DICETIME);
	}
	else if (state == READY)
	{
		if (PPU->ready_num == 0)
		{
			this->stepcount = step;
			state = ONBOARD;
			PPU->ready_num++;
			this->pos = step + this->pos_start - 1;
			//给观察者发送消息，飞机操作完毕，开始骰子操作
			this->notify(this, MVCEvent::DICETIME);
			//给观察者发送消息，飞机操作完毕，告知棋盘
			doFly = true;
			std::cout << "planenumber" << this->PPUNumber << "goONboard" << std::endl;
		}

	}
	else if (state == ONFINAL)
	{
		lastpos = pos;
		stepcount += step;
		pos += step;
		if (this->pos > this->pos_final_end)
		{
			pos = pos_final_end - (pos - pos_final_end);
		}
		//给观察者发送消息，飞机操作完毕，开始骰子操作
		this->notify(this, MVCEvent::DICETIME);
	}



}

void Plane_Client::Input(sf::Event& event, int diceNumber, bool& isInput)
{
	//当鼠标左键在飞机上释放时
	if (event.type == Event::MouseButtonReleased
		&& event.mouseButton.button == sf::Mouse::Left
		&& this->hitbox.contains((sf::Vector2f)sf::Mouse::getPosition(window)))
	{
		sf::Packet packet;

		sf::Uint32 data = 'PLNE';
		Client::Instance()->socket.send(&data, sizeof(sf::Uint32));
		packet << this->PPUNumber;
		//把飞机操作的结果发送给服务端
		Client::Instance()->socket.send(packet);
		this->move(diceNumber);

		isInput = true;
	}
}



void Plane_Client::Init()
{
	this->state = HOME;
	this->stepcount = 0;
	this->pos = 0;
	this->lastpos = 0;
	this->currentpos = this->pos_start;
	this->sprite.setRotation(0);
}

bool Plane_ClientPoolUnit::JudgeAvailable(int diceNumber)
{
	if (diceNumber == 6)
	{
		return true;
	}
	else
	{
		for (int i = 0;i < 4;i++)
		{
			if (plane_Client[i]->state != Plane_Client::HOME && plane_Client[i]->state != Plane_Client::FINAL)
				return true;
		}
	}

	return false;
}

void Plane_ClientPoolUnit::AddObserver(Observer* observer)
{
	for (int i = 0;i < 4;i++)
	{
		this->plane_Client[i]->addObserver(observer);
	}
}
void Plane_ClientPoolUnit::Update()
{
	int fineCount = 0;
	for (int i = 0;i < 4;i++)
	{
		plane_Client[i]->Update();
		if (plane_Client[i]->state == Plane_Client::FINAL)
		{
			fineCount += 1;
			if (fineCount == 4)
			{
				this->fine = true;
			}
		}
	}

}

void Plane_ClientPoolUnit::Render()
{
	for (int i = 0;i < 4;i++)
	{
		plane_Client[i]->Rander();
	}
}

void Plane_ClientPoolUnit::Input(sf::Event& event, int diceNumber)
{
	isInput = false;
	for (int i = 0;i < 4;i++)
	{
		if (!isInput)
			plane_Client[i]->Input(event, diceNumber, isInput);
	}
}


void Plane_ClientPoolUnit::Input(sf::Packet& packet, int diceNumber)
{
	//接收到操作的飞机的序号
	sf::Uint8 PlaneNumber;
	packet >> PlaneNumber;
	plane_Client[PlaneNumber]->move(diceNumber);

}

void Plane_ClientPool::Render()
{
	redPlane_Clientpool.Render();
	bluePlane_Clientpool.Render();
	yellowPlane_Clientpool.Render();
	greenPlane_Clientpool.Render();

	window.draw(turnsign);
};

void Plane_ClientPool::Update()
{
	redPlane_Clientpool.Update();
	bluePlane_Clientpool.Update();
	yellowPlane_Clientpool.Update();
	greenPlane_Clientpool.Update();

	if (clock.getElapsedTime().asMilliseconds() > 500)
	{
		SetTurnSignPos();
	}

}

Plane_ClientPool::Plane_ClientPool()
{
	//从文件中读取飞机的家的位置
	std::ifstream infile;
	infile.open("homepos.txt");
	for (int i = 0;i < 4;i++)
	{
		int a;
		infile >> a;
		greenPlane_Clientpool.plane_Client[i]->home_pos_x = a + ChessBoard::instance()->sprite.getPosition().x;
		infile >> a;
		greenPlane_Clientpool.plane_Client[i]->home_pos_y = a + ChessBoard::instance()->sprite.getPosition().y;
	}
	for (int i = 0;i < 4;i++)
	{
		int a;
		infile >> a;
		redPlane_Clientpool.plane_Client[i]->home_pos_x = a + ChessBoard::instance()->sprite.getPosition().x;
		infile >> a;
		redPlane_Clientpool.plane_Client[i]->home_pos_y = a + ChessBoard::instance()->sprite.getPosition().y;
	}
	for (int i = 0;i < 4;i++)
	{
		int a;
		infile >> a;
		yellowPlane_Clientpool.plane_Client[i]->home_pos_x = a + ChessBoard::instance()->sprite.getPosition().x;
		infile >> a;
		yellowPlane_Clientpool.plane_Client[i]->home_pos_y = a + ChessBoard::instance()->sprite.getPosition().y;
	}
	for (int i = 0;i < 4;i++)
	{
		int a;
		infile >> a;
		bluePlane_Clientpool.plane_Client[i]->home_pos_x = a + ChessBoard::instance()->sprite.getPosition().x;
		infile >> a;
		bluePlane_Clientpool.plane_Client[i]->home_pos_y = a + ChessBoard::instance()->sprite.getPosition().y;
	}

	//从文件中读取飞机的出发位置
	std::ifstream infile_2;
	infile_2.open("readypos.txt");
	int b;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		greenPlane_Clientpool.plane_Client[i]->ready_pos_x = b + ChessBoard::instance()->sprite.getPosition().x;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		greenPlane_Clientpool.plane_Client[i]->ready_pos_y = b + ChessBoard::instance()->sprite.getPosition().y;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		redPlane_Clientpool.plane_Client[i]->ready_pos_x = b + ChessBoard::instance()->sprite.getPosition().x;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		redPlane_Clientpool.plane_Client[i]->ready_pos_y = b + ChessBoard::instance()->sprite.getPosition().y;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		yellowPlane_Clientpool.plane_Client[i]->ready_pos_x = b + ChessBoard::instance()->sprite.getPosition().x;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		yellowPlane_Clientpool.plane_Client[i]->ready_pos_y = b + ChessBoard::instance()->sprite.getPosition().y;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		bluePlane_Clientpool.plane_Client[i]->ready_pos_x = b + ChessBoard::instance()->sprite.getPosition().x;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		bluePlane_Clientpool.plane_Client[i]->ready_pos_y = b + ChessBoard::instance()->sprite.getPosition().y;


	currentpool = &redPlane_Clientpool;
	std::cout << "red turn" << std::endl;

	tturnsign.loadFromFile("./data/UI/turnsign.png");
	turnsign.setTexture(tturnsign);
	turnsign.setOrigin(25, 25);
	SetTurnSignPos();

}

void Plane_ClientPool::Input(sf::Event& event, int diceNumber)
{
	currentpool->Input(event, diceNumber);
}

void Plane_ClientPool::SwitchToNextTurn()
{
	switch (TURN)
	{
	case RED:
		this->TURN = YELLOW;
		currentpool = &yellowPlane_Clientpool;
		std::cout << "yellow turn" << std::endl;
		break;
	case YELLOW:
		this->TURN = BLUE;
		currentpool = &bluePlane_Clientpool;
		std::cout << "blue turn" << std::endl;
		break;
	case BLUE:
		this->TURN = GREEN;
		currentpool = &greenPlane_Clientpool;
		std::cout << "green turn" << std::endl;
		break;
	case GREEN:
		this->TURN = RED;
		currentpool = &redPlane_Clientpool;
		std::cout << "red turn" << std::endl;
		break;
	default:
		break;
	}
	clock.restart();
}

void Plane_ClientPool::SetTurnSignPos()
{
	switch (TURN)
	{
	case RED:
		turnsign.setPosition(50 + 600 - 25, 100 + 25);
		break;
	case YELLOW:
		turnsign.setPosition(50 + 600 - 25, 100 + 600 - 25);
		break;
	case BLUE:
		turnsign.setPosition(50 + 25, 100 + 600 - 25);
		break;
	case GREEN:
		turnsign.setPosition(50 + 25, 100 + 25);
		break;
	default:
		break;
	}
}

void Plane_ClientPool::AddObserver(Observer* observer)
{
	this->redPlane_Clientpool.AddObserver(observer);
	this->bluePlane_Clientpool.AddObserver(observer);
	this->yellowPlane_Clientpool.AddObserver(observer);
	this->greenPlane_Clientpool.AddObserver(observer);
}