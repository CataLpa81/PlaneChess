#include"ChessBoard.h"
#include<iostream>
#include<fstream>

ChessBoard::ChessBoard()
{
	
	this->sprite.setPosition(50, 100);
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
		blocks[i].x = a + sprite.getPosition().x;
		infile >> a;
		blocks[i].y = a + sprite.getPosition().y;
	}
}

void ChessBoard::onNotify(Entity* entity_,MVCEvent event)
{
	if (event == MVCEvent::PLANEMOVE_ONBOARD)
	{
		if (dynamic_cast<Plane*>(entity_)->lastpos!=0)
		{
			this->blocks[dynamic_cast<Plane*>(entity_)->lastpos - 1].PopFromQueue(entity_);
		}
		this->blocks[dynamic_cast<Plane*>(entity_)->pos - 1].PushToQueue(entity_);
		this->blocks[dynamic_cast<Plane*>(entity_)->pos - 1].judgehit(dynamic_cast<Plane*>(entity_));
		
	}

	
}
void block::judgehit(Plane* plane_)
{
	if (entityvector.size() >= 2)
	{
		for (std::set<Entity*>::iterator iter=entityvector.begin();iter!=entityvector.end();)
		{
			if (dynamic_cast<Plane*>(*iter))
			{
				if (dynamic_cast<Plane*>(*iter)->PPU != plane_->PPU)
				{
					dynamic_cast<Plane*>(*iter)->Init();
					entityvector.erase(iter++);
				}
					
				else
				{
					++iter;
				}
			}
			
		}
	}
}
void block::PushToQueue(Entity* entity_)
{
	this->entityvector.insert(entity_);
}

void block::PopFromQueue(Entity* entity_)
{
	this->entityvector.erase(entity_);
}

