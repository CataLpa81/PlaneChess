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
};