#pragma once

#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include"ChessBoard.h"
#include"GameManager.h"

using namespace sf;

extern class RedPlane;
extern class YellowPlane;
extern class BluePlane;
extern class GreenPlane;
extern class PlanePool;

extern sf::RenderWindow window;

class Plane :public Entity,public Subject
{
public:
	virtual void Update();
	virtual void Input(sf::Event& event, int diceNumber);
	void move(int step);
	enum {
		HOME,
		READY,
		ONBOARD,
		FINAL
	}state = HOME;
	int home_pos_x, home_pos_y;
	int ready_pos_x, ready_pos_y;
	
	int pos_start, pos_end, pos_final_start, pos_final_end;
};

class PlanePoolUnit
{
public:
	void AddObserver(Observer* observer);
	void Update();
	void Rander();
	void Input(sf::Event& event, int diceNumber);
	bool JudgeAvailable(int diceNumber);
	Plane* plane[4];
	friend PlanePool;
};

class RedPlanePool:public PlanePoolUnit
{
public:
	friend PlanePool;
private:
	RedPlanePool();
};

class BluePlanePool :public PlanePoolUnit
{
public:
	friend PlanePool;
private:
	BluePlanePool();
};

class YellowPlanePool :public PlanePoolUnit
{
public:
	friend PlanePool;
private:
	YellowPlanePool();
};

class GreenPlanePool :public PlanePoolUnit
{
public:
	friend PlanePool;
private:
	GreenPlanePool();
};

class PlanePool
{
public:
	//µ¥ÀýÄ£Ê½
	static PlanePool* instance()
	{
		static PlanePool* instance = new PlanePool();
		return instance;
	}
	void AddObserver(Observer* observer);
	void SwitchToNextTurn();
	void Update();
	void Rander();
	void Input(sf::Event& event,int diceNumber);
	enum {
		RED,
		YELLOW,
		BLUE,
		GREEN,
	}TURN = RED;
	PlanePoolUnit* currentpool;
	RedPlanePool redplanepool;
	BluePlanePool blueplanepool;
	YellowPlanePool yellowplanepool;
	GreenPlanePool greenplanepool;
private:
	PlanePool();

};

class RedPlane : public Plane
{
public:
	RedPlane() {
		pos_start = 4;
		pos_end = 1;
		pos_final_start = 53;
		pos_final_end = 58;
		this->texture.loadFromFile("./data/Entity/red_player.png");
		this->sprite.setTexture(this->texture);
		this->sprite.setOrigin(this->texture.getSize().x / 2, this->texture.getSize().y / 2);
	}
};

class YellowPlane : public Plane
{
public:
	YellowPlane() {
		pos_start = 17;
		pos_end = 14;
		pos_final_start = 59;
		pos_final_end = 64;
		this->texture.loadFromFile("./data/Entity/yellow_player.png");
		this->sprite.setTexture(this->texture);
		this->sprite.setOrigin(this->texture.getSize().x / 2, this->texture.getSize().y / 2);
	}
};


class BluePlane : public Plane
{
public:
	BluePlane() {
		pos_start = 30;
		pos_end = 27;
		pos_final_start = 65;
		pos_final_end = 70;
		this->texture.loadFromFile("./data/Entity/blue_player.png");
		this->sprite.setTexture(this->texture);
		this->sprite.setOrigin(this->texture.getSize().x / 2, this->texture.getSize().y / 2);
	}
};


class GreenPlane : public Plane
{
public:
	GreenPlane() {
		pos_start = 43;
		pos_end = 40;
		pos_final_start = 71;
		pos_final_end = 76;
		this->texture.loadFromFile("./data/Entity/green_player.png");
		this->sprite.setTexture(this->texture);
		this->sprite.setOrigin(this->texture.getSize().x / 2, this->texture.getSize().y / 2);
	}
};