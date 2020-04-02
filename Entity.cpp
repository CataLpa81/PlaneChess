#include"Entity.h"
#include"ChessBoard.h"
#include<fstream>
#include<time.h>
#include"Plane.h"



void Entity::Update()
{
	this->x = chessboard->blocks[pos - 1].x;
	this->y = chessboard->blocks[pos - 1].y;
	this->sprite.setPosition(x, y);	
}


int Dice::createNumber()
{
	srand((int)time(NULL));
	int number = rand()%6+1;
	std::cout << "number = " << number << std::endl;
	this->state = UNROLLABLE;
	return number;
}

Dice::Dice()
{
	this->texture.loadFromFile("./data/Entity/dice2.jpg");
	this->sprite.setTexture(this->texture);
	this->x = 900;
	this->y = 700;
	this->sprite.setScale(0.5, 0.5);
	this->sprite.setPosition(x, y);
	this->hitbox = this->sprite.getGlobalBounds();
}

void Dice::input(sf::Event& event)
{
	if (this->state == ROLLABLE)
	{
		if (event.type == sf::Event::MouseButtonReleased &&
			event.mouseButton.button == sf::Mouse::Left)
		{
			if (this->hitbox.contains((sf::Vector2f)sf::Mouse::getPosition(window)) &&
				state == ROLLABLE)
			{
				std::cout << "dice clicked" << std::endl;
				Number = createNumber();
				this->state = UNROLLABLE;
			}
		}
	}
	
}

void Dice::Rander()
{
	window.draw(this->sprite);
}


void Dice::Update()
{}