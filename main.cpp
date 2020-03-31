#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include"ChessBoard.h"
#include"Entity.h"
#include<fstream>
#define WIDTH 1200
#define HEIGHT 800

using namespace sf;

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "CataLpa");

Texture tbk;
Sprite spbk;
PlanePool* planepool;


void Initial()
{
	planepool=&PlanePool::instance();
	window.setFramerateLimit(30);
	tbk.loadFromFile("./data/background/sky.jpg");
	spbk.setTexture(tbk);
	chessboard->texture.loadFromFile("./data/Background/chessboard.png");
	chessboard->sprite.setTexture(chessboard->texture);
}

void Input()
{
	sf::Event event;  //接受窗口事件
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) { // 检测关闭
			window.close();
		}
	}
}

void Update()
{
	planepool->Update();
}

void Rander()
{
	window.draw(spbk);
	window.draw(chessboard->sprite);
	planepool->Rander();
	window.display();
}

int main()
{
	Initial();
	while (1)
	{
		Input();
		Update();
		Rander();
	}
}
