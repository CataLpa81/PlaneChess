#pragma once
#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include"ChessBoard.h"
#include"ChessBoard_Client.h"
#include"Entity.h"
#include"Plane.h"
#include"GameManager.h"
#include"Dice.h"
#include"Scence.h"
#include"NetWork_Client.h"
#include"NetWork_Server.h"
#include"Audio.h"
#define WIDTH 1200
#define HEIGHT 800

using namespace std;

enum class GameScence
{
	BEGIN,
	LOCALGAME,
	NETGAME1,
	NETGAME2,
	NETGAME3,
	NETGAME
};

extern GameScence GP;


class Game
{
public:
	static Game* Instance()
	{
		static Game* instance = new Game();
		return instance;
	}
	void Initial();
	void Input();
	void Update();
	void Rander();
	void Run();

	Texture tbk;
	Sprite spbk;

	GameManager* gm;
	GameManagerClient* gmc;
	BeginInterface* bi;
	NetGame2_Scence* NS2;
	NetGame1_Scence* NS1;
	AudioManager* AM;


	bool IsServer=false;
	bool IsClient=false;
	Server* s;
	Client* c;
private:
	Game() {
		s = Server::Instance();
		c = Client::Instance();
	};

};