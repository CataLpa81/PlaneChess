#include"ChessBoard.h"
#include<iostream>
#include<fstream>

ChessBoard::ChessBoard()
{
	this->getdata();
	this->sprite.setPosition(50, 100);
}

void ChessBoard::getdata()
{
	
	std::ifstream infile;
	infile.open("pos.txt");
	int a;
	for (int i = 0;i < 76;i++)
	{
		infile >> a;
		std::cout << a << " ";
		blocks[i].x = a;
		infile >> a;
		blocks[i].y = a;
	}
}

