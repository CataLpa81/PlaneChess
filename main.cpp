#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include"ChessBoard.h"
#include"Entity.h"
#define WIDTH  800
#define HEIGHT 800

using namespace sf;

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "CataLpa");

Plane* redplayer = new RedPlane();
Plane* blueplayer = new BluePlane();
Plane* yellowplayer = new YellowPlane();
Plane* greenplayer = new GreenPlane();

ChessBoard* chessboard = new ChessBoard();

void Initial()
{
	window.setFramerateLimit(30);
	
	
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

}

void Rander()
{
	window.draw(redplayer->sprite);
	window.draw(greenplayer->sprite);
	window.draw(blueplayer->sprite);
	window.draw(chessboard->sprite);
	window.draw(yellowplayer->sprite);
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
