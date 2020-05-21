//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include"Game.h"

using namespace sf;
int main()
{
	std::cout << "hh" << std::endl;
	Game* game = Game::Instance();
	game->Run();
}
