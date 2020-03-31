#pragma once
#ifndef CHESSBOARD_H
#define CHESSBOARD_H


#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include"Entity.h"
using namespace sf;

extern class Entity;
extern class ChessBoard;
extern ChessBoard* chessboard;

class block
{
public:
	int rotation;
	int x, y;
	Entity* entity;
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

#endif // !CHESSBOARD_H