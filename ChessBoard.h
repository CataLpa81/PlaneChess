#pragma once

#include<list>
#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include"Entity.h"
#include"MVC.h"
#include"Plane.h"

#define BLOCKNUM 76
using namespace sf;

extern class Entity;
extern class ChessBoard;
extern class Plane;
extern enum MVCEvent;

class block
{
public:
	void PushToQueue(Entity* entity_);
	void PopFromQueue(Entity* entity_);
	void judgehit(Plane* plane_);
	int rotation;
	float x, y;
	std::list<Entity*> entityvector;
};


class ChessBoard:public Observer
{
public:
	//µ¥ÀýÄ£Ê½
	static ChessBoard* instance()
	{
		static ChessBoard* instance = new ChessBoard();
		return instance;
	}
	
	Texture texture;
	Sprite sprite;
	block blocks[BLOCKNUM];
	virtual void onNotify(Entity* entity_, MVCEvent event);
	void getdata();
	void Update();
private:
	ChessBoard();
};

