#pragma once
#ifndef ENTITY_H
#define ENTITY_H


#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include"ChessBoard.h"

extern class RedPlane;
extern class YellowPlane;
extern class BluePlane;
extern class GreenPlane;

using namespace sf;
extern sf::RenderWindow window;
extern RedPlane* redplane[4];
extern YellowPlane* yellowplane[4];
extern BluePlane* blueplane[4];
extern GreenPlane* greenplane[4];

class Entity
{
public:
	virtual void Update();
	virtual void Rander();
	int x, y,pos;
	Texture texture;
	Sprite sprite;
};

class Plane:public Entity
{
public:

	void move(int step);
	bool isHome=true;
	bool isAchieve=false;
};

class PlanePool
{
public:
	//µ¥ÀýÄ£Ê½
	static PlanePool& instance();
	void Update();
	void Rander();
	RedPlane* redplane[4];
	YellowPlane* yellowplane[4];
	BluePlane* blueplane[4];
	GreenPlane* greenplane[4];
private:
	PlanePool();

};

class RedPlane : public Plane
{
public:
	RedPlane() {
		
		this->texture.loadFromFile("./data/Entity/red_player.png");
		this->sprite.setTexture(this->texture);
		this->sprite.setOrigin(this->texture.getSize().x / 2, this->texture.getSize().y / 2);
	}
};

class YellowPlane : public Plane
{
public:
	YellowPlane() {
		
		this->texture.loadFromFile("./data/Entity/yellow_player.png");
		this->sprite.setTexture(this->texture);
		this->sprite.setOrigin(this->texture.getSize().x / 2, this->texture.getSize().y / 2);
	}
};


class BluePlane : public Plane
{
public:
	BluePlane() {
		
		this->texture.loadFromFile("./data/Entity/blue_player.png");
		this->sprite.setTexture(this->texture);
		this->sprite.setOrigin(this->texture.getSize().x / 2, this->texture.getSize().y / 2);
	}
};


class GreenPlane : public Plane
{
public:
	GreenPlane() {
	
		this->texture.loadFromFile("./data/Entity/green_player.png");
		this->sprite.setTexture(this->texture);
		this->sprite.setOrigin(this->texture.getSize().x / 2, this->texture.getSize().y / 2);
	}
};

#endif // !ENTITY_H
