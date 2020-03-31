#include"Entity.h"
#include"ChessBoard.h"
#include<fstream>




void Entity::Update()
{

	this->sprite.setPosition(x, y);
	
}

void Entity::Rander()
{

	window.draw(this->sprite);
}

void Plane::move(int step)
{

	pos += step;
	
}


void PlanePool::Rander()
{
	for (int i = 0;i < 4;i++){redplane[i]->Rander();}
	for (int i = 0;i < 4;i++){yellowplane[i]->Rander();}
	for (int i = 0;i < 4;i++){blueplane[i]->Rander();}
	for (int i = 0;i < 4;i++){greenplane[i]->Rander();}
};

void PlanePool::Update()
{
	for (int i = 0;i < 4;i++){redplane[i]->Update();}
	for (int i = 0;i < 4;i++){yellowplane[i]->Update();}
	for (int i = 0;i < 4;i++){blueplane[i]->Update();}
	for (int i = 0;i < 4;i++){greenplane[i]->Update();}
}

PlanePool::PlanePool()
{
	for (int i = 0;i < 4;i++){redplane[i] = new RedPlane();}
	for (int i = 0;i < 4;i++){yellowplane[i] = new YellowPlane();}
	for (int i = 0;i < 4;i++){blueplane[i] = new BluePlane();}
	for (int i = 0;i < 4;i++){greenplane[i] = new GreenPlane();}

	std::ifstream infile;
	infile.open("homepos.txt");
	for (int i = 0;i < 4;i++)
	{
		int a;
		infile >> a;
		greenplane[i]->x = a + chessboard->sprite.getPosition().x;
		infile >> a;
		greenplane[i]->y = a + chessboard->sprite.getPosition().y;
	}

	for (int i = 0;i < 4;i++)
	{
		int a;
		infile >> a;
		redplane[i]->x = a + chessboard->sprite.getPosition().x;
		infile >> a;
		redplane[i]->y = a + chessboard->sprite.getPosition().y;
	}

	for (int i = 0;i < 4;i++)
	{
		int a;
		infile >> a;
		yellowplane[i]->x = a + chessboard->sprite.getPosition().x;
		infile >> a;
		yellowplane[i]->y = a + chessboard->sprite.getPosition().y;
	}

	for (int i = 0;i < 4;i++)
	{
		int a;
		infile >> a;
		blueplane[i]->x = a + chessboard->sprite.getPosition().x;
		infile >> a;
		blueplane[i]->y = a + chessboard->sprite.getPosition().y;
	}
}