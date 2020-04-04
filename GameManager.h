#pragma once
#include"Plane.h"
#include"ChessBoard.h"
#include<fstream>
#include"Entity.h"
#include"MVC.h"

extern class PlanePool;
extern class Dice;

class GameManager:public Observer
{
public:
	static GameManager* instance(Dice* dice_, PlanePool* planepool_)
	{
		static GameManager* instance = new GameManager(dice_,planepool_);
		return instance;
	}
	virtual void onNotify(MVCEvent event);
	void GameLogic(sf::Event event);
	enum {
		PLANE,
		BRIGE_TOPLANE,
		BRIGE_TODICE,
		DICE
	}turn=DICE;
	Dice* dice;
	PlanePool* planepool;
private:
	GameManager(Dice* dice_,PlanePool* planepool_){
		dice = dice_;
		planepool = planepool_;
	}
};