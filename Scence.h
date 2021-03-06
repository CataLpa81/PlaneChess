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
	btnSound btnSd;

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
	void DisPlayFULL();
	void DisPlaySTARTED();

	InputBox IB1;
	InputBox* IB2;
private:
	NetGame1_Scence();
	Text t;
	Font f;
	Text t1;
	Font f1;
	Texture texture;
	Sprite sprite;
	btnJoinGame btnJG;
	btnBack btnB;
	btnSound btnSd;
	
	Clock c;

	bool isFull = false;
	bool isStart = false;
	
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
	Texture texture;
	Sprite sprite;


	Texture tRED;
	Sprite sRED;
	Texture tGREEN;
	Sprite sGREEN;
	Texture tYELLOW;
	Sprite sYELLOW;
	Texture tBLUE;
	Sprite sBLUE;

	Lable Lred;
	Lable Lgreen;
	Lable Lyellow;
	Lable Lblue;
	btnStartGame btnSG;
	btnSound btnSd;
	

	NetGame2_Scence();
	
};