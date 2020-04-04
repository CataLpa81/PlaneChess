#include"Entity.h"
#include"ChessBoard.h"
#include<fstream>
#include<time.h>
#include"Plane.h"
#include"GameManager.h"



void Entity::Update()
{
	this->x = chessboard->blocks[pos - 1].x;
	this->y = chessboard->blocks[pos - 1].y;
	this->sprite.setPosition(x, y);	
}

void Entity::Rander()
{
	window.draw(this->sprite);
}

int Dice::createNumber()
{
	srand((int)time(NULL));
	int number = rand()%6+1;
	std::cout << "number = " << number << std::endl;
	Number = number;
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
	if (event.type == Event::MouseButtonReleased
		&& event.mouseButton.button == sf::Mouse::Left
		&& this->hitbox.contains((sf::Vector2f)sf::Mouse::getPosition(window)))
	{
		createNumber();
		//给观察这发送消息，轮到飞机的操作时间
		this->notify(MVCEvent::PLANETIME);
	}
}

void Dice::Rander()
{
	window.draw(this->sprite);
}


void Dice::Update()
{}