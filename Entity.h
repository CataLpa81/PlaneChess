#pragma once
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include"MVC.h"

using namespace sf;

extern sf::RenderWindow window;

extern class Subject;
extern class Dice;

class Entity
{
public:
	virtual void Update();
	virtual void Rander();
	virtual void Init();
	float x, y;
	int pos;
	Texture texture;
	Sprite sprite;
	sf::FloatRect hitbox;
};

class Dice : public Entity,public Subject
{
public:
	//µ¥ÀýÄ£Ê½
	static Dice* instance()
	{
		static Dice* instance = new Dice();
		return instance;
	}
	virtual void Update();
	virtual void Rander();
	int createNumber();
	int Number;
	void input(sf::Event& event);

private:
	Dice();
};



