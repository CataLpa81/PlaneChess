#pragma once
#include<SFML/Graphics.hpp>
#include"Button.h"
#include"InputBox.h"
#include<stack>
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
	btnCreateGame btnCG;
	btnJoinGame btnJG;
};


class NetGame2_Scence
{
public:
	static NetGame2_Scence* Instance()
	{
		static NetGame2_Scence* instance = new NetGame2_Scence();
		return instance;
	}

	void Render();
	void Input(Event event);

private:
	NetGame2_Scence();
	Texture texture;
	Sprite sprite;
	btnStartGame btnSG;
	InputBox IB1;
	InputBox IB2;
};