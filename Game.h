#pragma once
#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include"ChessBoard.h"
#include"Entity.h"
#include"Plane.h"
#include"GameManager.h"
#include"Dice.h"
#include"BeginInterface.h"
#define WIDTH 1200
#define HEIGHT 800

enum class GameScence
{
	BEGIN,
	GAME,
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
	BeginInterface* bi;
private:
	Game() {};

};