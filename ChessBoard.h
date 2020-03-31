#pragma once

#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include"Entity.h"
using namespace sf;



class block
{
public:
	int x, y;
	

};

class BackGround
{

};

class ChessBoard
{
public:
	ChessBoard();
	Texture texture;
	Sprite sprite;
	block blocks[76];
	void getdata();
};

