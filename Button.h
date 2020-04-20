#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;

extern sf::RenderWindow window;

class Button
{
public:
	Button(sf::String s);
	virtual void OnPress() {};
	virtual void OnRelese() {};
	virtual void OnMove() {};
	void setPosition(int x,int y);
	void setOriginCenter();
	void InitTexture();
	void Render();
	void Input(Event event);
	
protected:
	enum
	{
		IDLE = 1,
		MOVE = 2,
		PRESS=3,
	};
	Vector2i TV;
	Texture texture;
	Sprite sprite;
	sf::FloatRect hitbox;
	bool isPressed = false;

	void setTexture(int frame);
	
};


class btnLocalGame :public Button
{
public:
	btnLocalGame():Button("./data/UI/btn_localgame.png"){}
	virtual ~btnLocalGame() {};
	virtual void OnPress();
	virtual void OnRelese();
};

class btnNetGame :public Button
{
public:
	btnNetGame() :Button("./data/UI/btn_netgame.png"){}
	virtual ~btnNetGame() {};
	virtual void OnPress();
	virtual void OnRelese();
};


class btnCreateGame :public Button
{
public:
	btnCreateGame() :Button("./data/UI/btn_creategame.png") {}
	virtual ~btnCreateGame() {};
	virtual void OnPress();
	virtual void OnRelese();
};


class btnJoinGame :public Button
{
public:
	btnJoinGame() :Button("./data/UI/btn_joingame.png") {}
	virtual ~btnJoinGame() {};
	virtual void OnPress();
	virtual void OnRelese();
};


class btnStartGame :public Button
{
public:
	btnStartGame():Button("./data/UI/btn_startgame.png") {}
	virtual ~btnStartGame() {};
	virtual void OnPress();
	virtual void OnRelese();
};
