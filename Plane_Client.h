#pragma once
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include"ChessBoard.h"
#include"Entity.h"
#include"NetWork_Client.h"
#include"NetWork_Server.h"
#include"InputBox.h"

#define Plane_ClientInit(ps,pe,pfs,pfe,lff)\
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

extern class Plane_ClientPoolUnit;
extern class RedPlane_Client;
extern class YellowPlane_Client;
extern class BluePlane_Client;
extern class GreenPlane_Client;
extern class Plane_ClientPool;
extern class Entity;
extern class block;

extern sf::RenderWindow window;

class Plane_Client :public Entity, public Subject
{
public:
	virtual void Update();
	void moveUpdate(block b1, block b2);
	virtual void Input(sf::Event& event, int diceNumber, bool& isInput);
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
	Plane_ClientPoolUnit* PPU;
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

	sf::Uint8 PPUNumber;


};
class RedPlane_Client : public Plane_Client
{
public:
	RedPlane_Client(Plane_ClientPoolUnit* PPU_) {
		Plane_ClientInit(4, 1, 53, 58, "./data/Entity/red_player.png");
		this->finaltexture.loadFromFile("./data/Entity/red_player_final.png");
		final_ready_rotation = 180;

	}
};
class YellowPlane_Client : public Plane_Client
{
public:
	YellowPlane_Client(Plane_ClientPoolUnit* PPU_) {
		Plane_ClientInit(17, 14, 59, 64, "./data/Entity/yellow_player.png");
		this->finaltexture.loadFromFile("./data/Entity/yellow_player_final.png");
		final_ready_rotation = -90;

	}
};
class BluePlane_Client : public Plane_Client
{
public:
	BluePlane_Client(Plane_ClientPoolUnit* PPU_) {
		Plane_ClientInit(30, 27, 65, 70, "./data/Entity/blue_player.png");
		this->finaltexture.loadFromFile("./data/Entity/blue_player_final.png");
		final_ready_rotation = 0;
	}
};
class GreenPlane_Client : public Plane_Client
{
public:
	GreenPlane_Client(Plane_ClientPoolUnit* PPU_) {
		Plane_ClientInit(43, 40, 71, 76, "./data/Entity/green_player.png");
		this->finaltexture.loadFromFile("./data/Entity/green_player_final.png");
		final_ready_rotation = 90;
	}
};
class Plane_ClientPoolUnit
{
public:
	void AddObserver(Observer* observer);
	void Update();
	void Render();
	void Input(sf::Event& event, int diceNumber);
	void Input(sf::Packet& packet, int diceNumber);
	bool JudgeAvailable(int diceNumber);
	bool fine = false;
	bool isInput;
	Plane_Client* plane_Client[4];
	int ready_num = 0;
	sf::String playerName ="null";
};

class RedPlane_ClientPool :public Plane_ClientPoolUnit
{
public:
	friend Plane_ClientPool;
private:
	RedPlane_ClientPool() { for (int i = 0;i < 4;i++) { this->plane_Client[i] = new RedPlane_Client(this); this->plane_Client[i]->PPUNumber = i; } }
};
class BluePlane_ClientPool :public Plane_ClientPoolUnit
{
public:
	friend Plane_ClientPool;
private:
	BluePlane_ClientPool() { for (int i = 0;i < 4;i++) { this->plane_Client[i] = new BluePlane_Client(this);this->plane_Client[i]->PPUNumber = i; } }
};
class YellowPlane_ClientPool :public Plane_ClientPoolUnit
{
public:
	friend Plane_ClientPool;
private:
	YellowPlane_ClientPool() { for (int i = 0;i < 4;i++) { this->plane_Client[i] = new YellowPlane_Client(this);this->plane_Client[i]->PPUNumber = i; } }
};
class GreenPlane_ClientPool :public Plane_ClientPoolUnit
{
public:
	friend Plane_ClientPool;
private:
	GreenPlane_ClientPool() { for (int i = 0;i < 4;i++) { this->plane_Client[i] = new GreenPlane_Client(this); this->plane_Client[i]->PPUNumber = i; } }
};

class Plane_ClientPool
{
public:
	//单例模式
	static Plane_ClientPool* instance()
	{
		static Plane_ClientPool* instance = new Plane_ClientPool();
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
	Plane_ClientPoolUnit* currentpool;
	RedPlane_ClientPool redPlane_Clientpool;
	BluePlane_ClientPool bluePlane_Clientpool;
	YellowPlane_ClientPool yellowPlane_Clientpool;
	GreenPlane_ClientPool greenPlane_Clientpool;

	Texture tturnsign;
	Lable Lred;
	Lable Lgreen;
	Lable Lblue;
	Lable Lyellow;
	Sprite turnsign;

	Clock clock;
private:
	Plane_ClientPool();

};
