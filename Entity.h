#pragma once
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

using namespace sf;
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

class RedPlane : public Plane
{
public:
	RedPlane() {
		this->texture.loadFromFile("./data/Entity/red_player.png");
		this->sprite.setTexture(this->texture);
	}
};

class YellowPlane : public Plane
{
public:
	YellowPlane() {
		this->texture.loadFromFile("./data/Entity/yellow_player.png");
		this->sprite.setTexture(this->texture);
	}
};


class BluePlane : public Plane
{
public:
	BluePlane() {
		this->texture.loadFromFile("./data/Entity/blue_player.png");
		this->sprite.setTexture(this->texture);
	}
};


class GreenPlane : public Plane
{
public:
	GreenPlane() {
		this->texture.loadFromFile("./data/Entity/green_player.png");
		this->sprite.setTexture(this->texture);
	}
};

