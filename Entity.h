#pragma once
#ifndef ENTITY_H
#define ENTITY_H


#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include"ChessBoard.h"



using namespace sf;

extern sf::RenderWindow window;



class Entity
{
public:
	virtual void Update();
	virtual void Rander();
	int x, y;
	int pos;
	Texture texture;
	Sprite sprite;
	sf::FloatRect hitbox;
};

class Dice : public Entity
{
public:
	//µ¥ÀýÄ£Ê½
	static Dice* instance()
	{
		static Dice* instance = new Dice();
		return instance;
	}
	enum {
		ROLLABLE,
		UNROLLABLE
	}state=ROLLABLE;
	virtual void Update();
	virtual void Rander();
	int createNumber();
	int Number;
	void input(sf::Event& event);

private:
	Dice();
};



#endif // !ENTITY_H
