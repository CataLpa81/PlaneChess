#pragma once
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include"ChessBoard.h"
#include"GameManager.h"
#include"Entity.h"

#define PlaneInit(ps,pe,pfs,pfe,lff)\
this->PPU=PPU_;\
pos_start = ps;\
pos_end = pe;\
pos_final_start = pfs;\
pos_final_end = pfe;\
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

extern sf::RenderWindow window;

class Plane :public Entity,public Subject
{
public:
	virtual void Update();
	virtual void Input(sf::Event& event, int diceNumber);
	virtual void Init();
	void move(int step);
	enum {
		HOME,
		READY,
		ONBOARD,
		ONFINAL,
		FINAL
	}state = HOME;
	PlanePoolUnit* PPU;
	int lastpos = 0;
	//已经走过的格子数
	int stepcount=0;
	//家的位置
	int home_pos_x, home_pos_y;
	//准备起飞的位置
	int ready_pos_x, ready_pos_y;
	//飞机的各种位置
	int pos_start, pos_end, pos_final_start, pos_final_end;
};
class RedPlane : public Plane
{
public:
	RedPlane(PlanePoolUnit* PPU_) { PlaneInit(4, 1, 53, 58, "./data/Entity/red_player.png"); }
};
class YellowPlane : public Plane
{
public:
	YellowPlane(PlanePoolUnit* PPU_) { PlaneInit(17, 14, 49, 64, "./data/Entity/yellow_player.png"); }
};

class BluePlane : public Plane
{
public:
	BluePlane(PlanePoolUnit* PPU_) { PlaneInit(30, 27, 65, 70, "./data/Entity/blue_player.png"); }
};
class GreenPlane : public Plane
{
public:
	GreenPlane(PlanePoolUnit* PPU_) { PlaneInit(43, 40, 71, 76, "./data/Entity/green_player.png"); }
};
class PlanePoolUnit
{
public:
	void AddObserver(Observer* observer);
	void Update();
	void Rander();
	void Input(sf::Event& event, int diceNumber);
	bool JudgeAvailable(int diceNumber);
	bool fine=false;
	Plane* plane[4];
};

class RedPlanePool:public PlanePoolUnit
{
public:
	friend PlanePool;
private:
	RedPlanePool(){ for (int i = 0;i < 4;i++)this->plane[i] = new RedPlane(this); }
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
