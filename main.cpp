#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include"Game.h"

using namespace sf;
int main()
{
	Game* game = Game::Instance();
	game->Run();
}
