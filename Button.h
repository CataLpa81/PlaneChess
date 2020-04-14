#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;

extern sf::RenderWindow window;

class Button
{
public:
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
	btnLocalGame();
	virtual ~btnLocalGame() {};
	virtual void OnPress();
	virtual void OnRelese();
};