#pragma once

#include"ChessBoard.h"
#include<fstream>
#include"Entity.h"
#include"MVC.h"
#include"Plane.h"
#include"Plane_Client.h"
#include"Dice.h"
#include"Dice_Client.h"
#include"NetWork_Client.h"
#include"NetWork_Server.h"

extern class ChessBoard;
extern class PlanePool;
extern class Dice;

class GameManager:public Observer
{
public:
	static GameManager* instance(Dice* dice_, PlanePool* planepool_, ChessBoard* chessboard)
	{
		static GameManager* instance = new GameManager(dice_,planepool_,chessboard);
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
	GameManager(Dice* dice_,PlanePool* planepool_, ChessBoard* chessboard_){
		chessboard = chessboard_;
		dice = dice_;
		planepool = planepool_;
	}


};


class GameManagerClient :public Observer
{
public:
	static GameManagerClient* instance(Dice_Client* dice_, Plane_ClientPool* planepool_, ChessBoard* chessboard)
	{
		static GameManagerClient* instance = new GameManagerClient(dice_, planepool_, chessboard);
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
	GameManagerClient(Dice_Client* dice_, Plane_ClientPool* planepool_, ChessBoard* chessboard_) {
		chessboard = chessboard_;
		dice = dice_;
		planepool = planepool_;
	}


};