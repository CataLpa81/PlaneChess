#pragma once
#pragma once
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include"ChessBoard.h"
#include"Entity.h"
#include"NetWork_Client.h"
#include"NetWork_Server.h"

#define PlaneInit(ps,pe,pfs,pfe,lff)\
this->PPU=PPU_;\
pos_start = ps;\
pos_end = pe;\
pos_final_start = pfs;\
pos_final_end = pfe;\
currentpos=pos_start;\
this->texture.loadFromFile(lff);\
this->sprite.setTexture(this->texture);\
this->sprite.setOrigin(this->texture.getSize().x / 2, this->texture.getSize().y / 2)


using namespace sf;

extern class PlanePoolUnit;
extern class RedPlane;
extern class YellowPlane;
extern class BluePlane;
extern class GreenPlane;
extern class PlanePool;
extern class Entity;
extern class block;

extern sf::RenderWindow window;

class Plane :public Entity, public Subject
{
public:
	virtual void Update();
	void moveUpdate(block b1, block b2);
	virtual void Input(sf::Event& event, int diceNumber);
	virtual void Init();
	void move(int step);
	void setrotation();
	void fly();
	enum {
		HOME,
		READY,
		ONBOARD,
		ONFINAL,
		FINAL
	}state = HOME;
	PlanePoolUnit* PPU;
	Texture finaltexture;
	int lastpos = 0;
	//已经走过的格子数
	int stepcount = 0;
	//家的位置
	int home_pos_x, home_pos_y;
	//准备起飞的位置
	int ready_pos_x, ready_pos_y;
	//飞机的各种位置
	int pos_start, pos_end, pos_final_start, pos_final_end;
	//飞行动画的步进
	float movespeed = 0.2;

	int currentpos;

	bool doFly;

	float final_ready_rotation;


};
class RedPlane : public Plane
{
public:
	RedPlane(PlanePoolUnit* PPU_) {
		PlaneInit(4, 1, 53, 58, "./data/Entity/red_player.png");
		this->finaltexture.loadFromFile("./data/Entity/red_player_final.png");
		final_ready_rotation = 180;

	}
};
class YellowPlane : public Plane
{
public:
	YellowPlane(PlanePoolUnit* PPU_) {
		PlaneInit(17, 14, 59, 64, "./data/Entity/yellow_player.png");
		this->finaltexture.loadFromFile("./data/Entity/yellow_player_final.png");
		final_ready_rotation = -90;

	}
};
class BluePlane : public Plane
{
public:
	BluePlane(PlanePoolUnit* PPU_) {
		PlaneInit(30, 27, 65, 70, "./data/Entity/blue_player.png");
		this->finaltexture.loadFromFile("./data/Entity/blue_player_final.png");
		final_ready_rotation = 0;
	}
};
class GreenPlane : public Plane
{
public:
	GreenPlane(PlanePoolUnit* PPU_) {
		PlaneInit(43, 40, 71, 76, "./data/Entity/green_player.png");
		this->finaltexture.loadFromFile("./data/Entity/green_player_final.png");
		final_ready_rotation = 90;
	}
};
class PlanePoolUnit
{
public:
	void AddObserver(Observer* observer);
	void Update();
	void Render();
	void Input(sf::Event& event, int diceNumber);
	bool JudgeAvailable(int diceNumber);
	bool fine = false;
	Plane* plane[4];
	int ready_num = 0;
};

class RedPlanePool :public PlanePoolUnit
{
public:
	friend PlanePool;
private:
	RedPlanePool() { for (int i = 0;i < 4;i++)this->plane[i] = new RedPlane(this); }
};
class BluePlanePool :public PlanePoolUnit
{
public:
	friend PlanePool;
private:
	BluePlanePool() { for (int i = 0;i < 4;i++)this->plane[i] = new BluePlane(this); }
};
class YellowPlanePool :public PlanePoolUnit
{
public:
	friend PlanePool;
private:
	YellowPlanePool() { for (int i = 0;i < 4;i++)this->plane[i] = new YellowPlane(this); }
};
class GreenPlanePool :public PlanePoolUnit
{
public:
	friend PlanePool;
private:
	GreenPlanePool() { for (int i = 0;i < 4;i++)this->plane[i] = new GreenPlane(this); }
};

class PlanePool
{
public:
	//单例模式
	static PlanePool* instance()
	{
		static PlanePool* instance = new PlanePool();
		return instance;
	}
	void AddObserver(Observer* observer);
	void SwitchToNextTurn();
	void Update();
	void Render();
	void Input(sf::Event& event, int diceNumber);
	void SetTurnSignPos();
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

	Texture tturnsign;
	Sprite turnsign;

	Clock clock;
private:
	PlanePool();

};
