#include"Plane.h"
#include"ChessBoard.h"
#include<fstream>
#include<math.h>






void Plane::Update()
{
	ChessBoard* cb = ChessBoard::instance();

	if (state == ONBOARD || state == ONFINAL)
	{
		if (currentpos==pos_start)
		{
			block b;
			b.x = ready_pos_x;
			b.y = ready_pos_y;
			moveUpdate(b, cb->blocks[currentpos-1],currentpos);
		}
		else if (currentpos !=pos_start)
		{
			int ls = ((currentpos == 1) ? 51 : (currentpos - 2));
			if (currentpos == pos_final_start)
				ls = pos_end-1;
			moveUpdate(cb->blocks[ls], cb->blocks[currentpos - 1], currentpos);
		}

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

void Plane::moveUpdate(block b1,block b2,int &cp)
{
	ChessBoard* cb = ChessBoard::instance();
		if (this->x != cb->blocks[cp - 1].x
			|| this->y != cb->blocks[cp - 1].y )
		{
				float dis_x = b2.x - b1.x;
				float dis_y = b2.y - b1.y;
				this->x += dis_x * movespeed;
				this->y += dis_y * movespeed;
		}

		if (abs(cb->blocks[cp - 1].x - this->x) < 0.001
			&& abs(cb->blocks[cp - 1].y - this->y) < float(0.001))
		{
			this->x = cb->blocks[cp - 1].x ;
			this->y = cb->blocks[cp - 1].y ;
			if (cp != pos)
				cp += 1;
			if(this->state==ONBOARD)
			if (cp > 52)
				cp -= 52;
			if (cp == pos_end + 1)
				cp = pos_final_start;
		}
}

void Plane::move(int step)
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
		//如果踩在第一个多次飞行的格子上
		if (this->stepcount==14)
		{
			this->stepcount += 16;
			this->pos = this->pos_start + 29;
		}
		//如果踩在第二个多次飞行的格子上
		else if (this->stepcount == 18)
		{
			this->stepcount += 16;
			this->pos = this->pos_start+33;
		}
		//如果踩在同颜色的格子上
		else if ((stepcount + 2) % 4 == 0 && stepcount < 50)
		{

			this->stepcount += 4;
			this->pos += 4;
			if (this->pos > 52)
			{
				this->pos -= 52;
			}
		}
		if (this->pos > 52)
		{
			this->pos -= 52;
		}
		
		if (this->stepcount > 50)
		{
			this->state = ONFINAL;
			this->pos = stepcount - 50 + pos_final_start-1;
			if (this->pos == this->pos_final_end)
				this->state = FINAL;
		}
		
		//给观察者发送消息，飞机操作完毕，开始骰子操作
		this->notify(this,MVCEvent::DICETIME);
		//给观察者发送消息，飞机操作完毕，告知棋盘
		this->notify(this, MVCEvent::PLANEMOVE_ONBOARD);
	}
	else if (state == HOME&&step == 6)
	{
		stepcount = 0;
		state = READY;
		//给观察者发送消息，飞机操作完毕，开始骰子操作
		this->notify(this,MVCEvent::DICETIME);
	}
	else if (state == READY)
	{
		this->stepcount = step;
		state = ONBOARD;
		this->pos = step+this->pos_start-1;
		if (step == 2 || step == 6)
		{
			this->stepcount += 4;
			this->pos += 4;
		}
		//给观察者发送消息，飞机操作完毕，开始骰子操作
		this->notify(this,MVCEvent::DICETIME);
		//给观察者发送消息，飞机操作完毕，告知棋盘
		this->notify(this, MVCEvent::PLANEMOVE_ONBOARD);
	}
	else if (state == ONFINAL)
	{
		lastpos = pos;
		stepcount += step;
		pos += step;
		if (this->pos == this->pos_final_end)
		{
			this->state = FINAL;
		}
			
		else if (this->pos > this->pos_final_end)
		{
			pos = pos_final_end - (pos - pos_final_end);
		}
		//给观察者发送消息，飞机操作完毕，开始骰子操作
		this->notify(this,MVCEvent::DICETIME);
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

void Plane::Init()
{
	this->state = HOME;
	this->stepcount = 0;
	this->pos = 0;
	this->lastpos = 0;
	this->currentpos = this->pos_start;
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
			if (plane[i]->state != Plane::HOME&&plane[i]->state!=Plane::FINAL)
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
	int fineCount = 0;
	for (int i = 0;i < 4;i++)
	{
		plane[i]->Update();
		if (plane[i]->state == Plane::FINAL)
		{	
			fineCount += 1;
			if (fineCount == 4)
			{
				this->fine = true;
			}
		}
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
		greenplanepool.plane[i]->home_pos_x = a + ChessBoard::instance()->sprite.getPosition().x;
		infile >> a;
		greenplanepool.plane[i]->home_pos_y = a + ChessBoard::instance()->sprite.getPosition().y;
	}
	for (int i = 0;i < 4;i++)
	{
		int a;
		infile >> a;
		redplanepool.plane[i]->home_pos_x = a + ChessBoard::instance()->sprite.getPosition().x;
		infile >> a;
		redplanepool.plane[i]->home_pos_y = a + ChessBoard::instance()->sprite.getPosition().y;
	}
	for (int i = 0;i < 4;i++)
	{
			int a;
			infile >> a;
			yellowplanepool.plane[i]->home_pos_x = a + ChessBoard::instance()->sprite.getPosition().x;
			infile >> a;
			yellowplanepool.plane[i]->home_pos_y = a + ChessBoard::instance()->sprite.getPosition().y;
	}
	for (int i = 0;i < 4;i++)
	{
			int a;
			infile >> a;
			blueplanepool.plane[i]->home_pos_x = a + ChessBoard::instance()->sprite.getPosition().x;
			infile >> a;
			blueplanepool.plane[i]->home_pos_y = a + ChessBoard::instance()->sprite.getPosition().y;
	}

	//从文件中读取飞机的出发位置
	std::ifstream infile_2;
	infile_2.open("readypos.txt");
	int b;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		greenplanepool.plane[i]->ready_pos_x = b + ChessBoard::instance()->sprite.getPosition().x;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		greenplanepool.plane[i]->ready_pos_y = b + ChessBoard::instance()->sprite.getPosition().y;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		redplanepool.plane[i]->ready_pos_x = b + ChessBoard::instance()->sprite.getPosition().x;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		redplanepool.plane[i]->ready_pos_y = b + ChessBoard::instance()->sprite.getPosition().y;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		yellowplanepool.plane[i]->ready_pos_x = b + ChessBoard::instance()->sprite.getPosition().x;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		yellowplanepool.plane[i]->ready_pos_y = b + ChessBoard::instance()->sprite.getPosition().y;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		blueplanepool.plane[i]->ready_pos_x = b + ChessBoard::instance()->sprite.getPosition().x;
	infile_2 >> b;
	for (int i = 0;i < 4;i++)
		blueplanepool.plane[i]->ready_pos_y = b + ChessBoard::instance()->sprite.getPosition().y;


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