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




