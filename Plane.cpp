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
		this->x = ready_pos_x + chessboard->sprite.getPosition().x;
		this->x = ready_pos_y + chessboard->sprite.getPosition().y;
	}

	this->sprite.setPosition(x, y);
	hitbox = this->sprite.getGlobalBounds();
}

void Entity::Rander()
{

	window.draw(this->sprite);
}

void Plane::move(int step)
{
	pos += step;
}

void Plane::Input(sf::Event& event)
{
	PlanePool* planepool = PlanePool::instance();
	Dice* dice = Dice::instance();
	if (event.type == sf::Event::MouseButtonReleased &&
		event.mouseButton.button == sf::Mouse::Left)
	{
		std::cout << "release1" << std::endl;
		if (this->hitbox.contains((sf::Vector2f)sf::Mouse::getPosition(window))
			&& dice->state==Dice::UNROLLABLE)
		{
			switch (state)
			{
			case Plane::HOME:
				if (dice->Number == 6)
				{
					this->state = READY;
					dice->state = Dice::ROLLABLE;
				}
				break;
			case Plane::READY:
				this->state = ONBOARD;
				this->pos = dice->Number;
				dice->state = Dice::ROLLABLE;
				if (dice->Number != 6)
					planepool->SwitchToNextTurn();
				break;
			case Plane::ONBOARD:
				this->pos += dice->Number;
				dice->state = Dice::ROLLABLE;
				if (dice->Number != 6)
					planepool->SwitchToNextTurn();
				break;
			case Plane::FINAL:
				break;
			default:
				break;
			}
			
		}
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

void PlanePoolUnit::Input(sf::Event& event)
{
	this->available = false;
	Dice* dice = Dice::instance();
	if (dice->Number == 6)
		this->available = true;
	else
	{
		for (int i = 0;i < 4;i++)
		{
			if (this->plane[i]->state != Plane::HOME)
			{
				available = true;
				break;
			}
				
		}
	}
	if (this->available == false)
	{
		PlanePool* planepool = PlanePool::instance();
		planepool->SwitchToNextTurn();
		dice->state = Dice::ROLLABLE;
	}
	for (int i = 0;i < 4;i++)
	{
		this->plane[i]->Input(event);
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
	std::ifstream infile;
	std::ifstream infile_2;
	infile.open("homepos.txt");
	infile_2.open("readypos.txt");
	for (int i = 0;i < 4;i++)
	{
		int a;
		infile >> a;
		greenplanepool.plane[i]->home_pos_x = a + chessboard->sprite.getPosition().x;
		infile >> a;
		greenplanepool.plane[i]->home_pos_y = a + chessboard->sprite.getPosition().y;
		infile_2 >> a;
		greenplanepool.plane[i]->ready_pos_x = a + chessboard->sprite.getPosition().x;
		infile_2 >> a;
		greenplanepool.plane[i]->ready_pos_y = a + chessboard->sprite.getPosition().y;
	}

	for (int i = 0;i < 4;i++)
	{
		int a;
		infile >> a;
		redplanepool.plane[i]->home_pos_x = a + chessboard->sprite.getPosition().x;
		infile >> a;
		redplanepool.plane[i]->home_pos_y = a + chessboard->sprite.getPosition().y;
		infile_2 >> a;
		redplanepool.plane[i]->ready_pos_x = a + chessboard->sprite.getPosition().x;
		infile_2 >> a;
		redplanepool.plane[i]->ready_pos_y = a + chessboard->sprite.getPosition().y;
	}
	for (int i = 0;i < 4;i++)
	{
			int a;
			infile >> a;
			yellowplanepool.plane[i]->home_pos_x = a + chessboard->sprite.getPosition().x;
			infile >> a;
			yellowplanepool.plane[i]->home_pos_y = a + chessboard->sprite.getPosition().y;
			infile_2 >> a;
			yellowplanepool.plane[i]->ready_pos_x = a + chessboard->sprite.getPosition().x;
			infile_2 >> a;
			yellowplanepool.plane[i]->ready_pos_y = a + chessboard->sprite.getPosition().y;
	}

	for (int i = 0;i < 4;i++)
	{
			int a;
			infile >> a;
			blueplanepool.plane[i]->home_pos_x = a + chessboard->sprite.getPosition().x;
			infile >> a;
			blueplanepool.plane[i]->home_pos_y = a + chessboard->sprite.getPosition().y;
			infile_2 >> a;
			blueplanepool.plane[i]->ready_pos_x = a + chessboard->sprite.getPosition().x;
			infile_2 >> a;
			blueplanepool.plane[i]->ready_pos_y = a + chessboard->sprite.getPosition().y;
	}

	std::cout << "red turn" << std::endl;
	
}

void PlanePool::Input(sf::Event& event)
{
	Dice* dice = Dice::instance();
	if (dice->state == Dice::UNROLLABLE)
	{
		for (int i = 0;i < 4;i++)
		{
			switch (TURN)
			{
			case PlanePool::RED:
				redplanepool.Input(event);
				break;
			case PlanePool::BLUE:
				blueplanepool.Input(event);
				break;
			case PlanePool::YELLOW:
				yellowplanepool.Input(event);
				break;
			case PlanePool::GREEN:
				greenplanepool.Input(event);
				break;
			default:
				break;
			}
		}
	}
	
}

void PlanePool::SwitchToNextTurn()
{
	switch(TURN)
	{
	case RED:
		this->TURN = YELLOW;
		std::cout << "yellow turn"<< std::endl;
		break;
	case YELLOW:
		this->TURN = BLUE;
		std::cout << "blue turn" << std::endl;
		break;
	case BLUE:
		this->TURN = GREEN;
		std::cout << "green turn" << std::endl;
		break;
	case GREEN:
		this->TURN = RED;
		std::cout << "red turn" << std::endl;
		break;
	default:
		break;
	}
}