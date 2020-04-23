#pragma once
#pragma once

#include<list>
#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include"Entity.h"
#include"MVC.h"
#include"Plane_Client.h"

#define BLOCKNUM 76
using namespace sf;

extern class Entity;
extern class ChessBoard_Client;
extern class Plane_Client;
extern enum MVCEvent;

class block_Client
{
public:
	void PushToQueue(Entity* entity_);
	void PopFromQueue(Entity* entity_);
	void judgehit(Plane_Client* plane_);
	int rotation;
	float x, y;
	std::list<Entity*> entityvector;
};


class ChessBoard_Client :public Observer
{
public:
	//µ¥ÀýÄ£Ê½
	static ChessBoard_Client* instance()
	{
		static ChessBoard_Client* instance = new ChessBoard_Client();
		return instance;
	}

	Texture texture;
	Sprite sprite;
	block_Client blocks[BLOCKNUM];
	virtual void onNotify(Entity* entity_, MVCEvent event);
	void getdata();
	void Update();
private:
	ChessBoard_Client();
};

