#pragma once

#include"ChessBoard.h"
#include<fstream>
#include"Entity.h"
#include"MVC.h"
#include"Plane.h"
#include"Plane_Client.h"
#include"Dice.h"
#include"Dice_Client.h"


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
	virtual void onNotify(Entity* entity_,MVCEvent event);
	void GameUpdateLogic();
	void GameInputLogic(sf::Event event);
	void GameRenderLogic();
private:
	GameManager(){
		chessboard = ChessBoard::instance();
		dice = Dice::instance();
		planepool = PlanePool::instance();
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
	ChessBoard* chessboard;
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
private:
	GameManagerClient();
};