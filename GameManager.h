#pragma once

#include"ChessBoard.h"
#include"ChessBoard_Client.h"
#include<fstream>
#include"Entity.h"
#include"MVC.h"
#include"Plane.h"
#include"Plane_Client.h"
#include"Dice.h"
#include"Dice_Client.h"
#include"Button.h"
#include"ChatRoom.h"




extern class Plane_ClientPool;
extern class Dice_Client;


class GameManager:public Observer
{
public:
	static GameManager* instance()
	{
		static GameManager* instance = new GameManager();
		return instance;
	}
	enum {
		PLANE,
		BRIGE_TOPLANE,
		BRIGE_TODICE,
		DICE
	}turn = DICE;
	ChessBoard* chessboard;
	Dice* dice;
	PlanePool* planepool;
	btnBack btnB;
	btnSound btnSd;
	virtual void onNotify(Entity* entity_,MVCEvent event);
	void GameUpdateLogic();
	void GameInputLogic(sf::Event event);
	void GameRenderLogic();
private:
	GameManager(){
		chessboard = ChessBoard::instance();
		dice = Dice::instance();
		planepool = PlanePool::instance();
		btnB.setPosition(100, 50);
		this->btnSd.setPosition(100, 100);
	}


};


class GameManagerClient :public Observer
{
public:
	static GameManagerClient* instance()
	{
		static GameManagerClient* instance = new GameManagerClient();
		return instance;
	}
	enum {
		PLANE,
		BRIGE_TOPLANE,
		BRIGE_TODICE,
		DICE
	}turn = DICE;

	Dice_Client* dice;
	Plane_ClientPool* planepool;
	enum {
		RED,
		YELLOW,
		BLUE,
		GREEN
	}Player;
	virtual void onNotify(Entity* entity_, MVCEvent event);
	void GameUpdateLogic();
	void GameInputLogic(sf::Event event);
	void GameRenderLogic();

	btnSound btnSd;
	ChatRoom* CR;
	
private:
	GameManagerClient();
};