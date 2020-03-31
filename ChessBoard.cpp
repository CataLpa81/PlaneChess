#include"ChessBoard.h"
#include<iostream>
#include<fstream>



ChessBoard::ChessBoard()
{
	this->getdata();
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
		this->blocks[i].x = a;
		infile >> a;
		this->blocks[i].y = a;
	}
}

