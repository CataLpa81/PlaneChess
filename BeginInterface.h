#pragma once
#include<SFML/Graphics.hpp>
#include"Button.h"
using namespace sf;

class BeginInterface
{
public:
	static BeginInterface* Instance()
	{
		static BeginInterface* instance = new BeginInterface();
		return instance;
	}
	void Render();
	void Input(Event event);

private:
	BeginInterface();
	Texture texture;
	Sprite sprite;
	btnLocalGame btnLG;
	btnNetGame btnNG;
};


class NetGame1_Scence
{
public:
	static NetGame1_Scence* Instance()
	{
		static NetGame1_Scence* instance = new NetGame1_Scence();
		return instance;
	}

	void Render();
	void Input(Event event);

private:
	NetGame1_Scence();
	Texture texture;
	Sprite sprite;
	

};