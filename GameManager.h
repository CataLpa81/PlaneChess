#pragma once
#include"Plane.h"
#include"ChessBoard.h"
#include<fstream>
#include"Entity.h"
#include"MVC.h"
#include"Dice.h"
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