#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include"ChessBoard.h"
#include"Entity.h"
#include"Plane.h"
#include"GameManager.h"
#define WIDTH 1200
#define HEIGHT 800

using namespace sf;

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "CataLpa");

Texture tbk;
Sprite spbk;



GameManager* gm;

void Initial()
{
	window.setFramerateLimit(140);
	gm = GameManager::instance(Dice::instance(), PlanePool::instance(), ChessBoard::instance());
	gm->dice->addObserver(gm);
	gm->planepool->AddObserver(gm);
	gm->planepool->AddObserver(gm->chessboard);
	window.setFramerateLimit(10);
	tbk.loadFromFile("./data/background/sky.jpg");
	spbk.setTexture(tbk);
	ChessBoard::instance()->texture.loadFromFile("./data/Background/chessboard.png");
	ChessBoard::instance()->sprite.setTexture(ChessBoard::instance()->texture);
}

void Input()
{
	
	sf::Event event;  //接受窗口事件
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) { // 检测关闭
			window.close();
		}
		gm->GameInputLogic(event);
	}


}

void Update()
{
	gm->GameUpdateLogic();
}

void Rander()
{
	window.draw(spbk);
	window.draw(ChessBoard::instance()->sprite);
	gm->planepool->Rander();
	gm->dice->Rander();
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
