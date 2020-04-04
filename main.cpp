#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include"ChessBoard.h"
#include"Entity.h"
#include<fstream>
#include"Plane.h"
#include"GameManager.h"
#define WIDTH 1200
#define HEIGHT 800

using namespace sf;

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "CataLpa");

Texture tbk;
Sprite spbk;

ChessBoard* chessboard = ChessBoard::instance();

GameManager* gm;

void Initial()
{
	PlanePool* planepool = PlanePool::instance();
	Dice* dice = Dice::instance();
	gm = GameManager::instance(dice, planepool);
	gm->dice->addObserver(gm);
	gm->planepool->AddObserver(gm);
	window.setFramerateLimit(10);
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
		gm->GameLogic(event);
	}


}

void Update()
{
	gm->planepool->Update();
}

void Rander()
{
	window.draw(spbk);
	window.draw(chessboard->sprite);
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
