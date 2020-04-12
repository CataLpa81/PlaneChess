#include"Entity.h"
#include"ChessBoard.h"
#include<fstream>
#include<time.h>
#include"Plane.h"
#include"GameManager.h"



void Entity::Update()
{
	this->x = ChessBoard::instance()->blocks[pos - 1].x;
	this->y = ChessBoard::instance()->blocks[pos - 1].y;
	this->sprite.setPosition(x, y);	
}

void Entity::Rander()
{
	window.draw(this->sprite);
}

void Entity::Init()
{}

