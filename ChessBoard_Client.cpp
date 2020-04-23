#include"ChessBoard_Client.h"
#include<iostream>
#include<fstream>

ChessBoard_Client::ChessBoard_Client()
{

	this->sprite.setPosition(50, 100);
	this->getdata();
}

void ChessBoard_Client::getdata()
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
void ChessBoard_Client::Update()
{
	for (int i = 0;i < BLOCKNUM;i++)
	{
		if (this->blocks[i].entityvector.size() != 0)
		{
			int offset = 0;
			for (std::list<Entity*>::iterator iter = this->blocks[i].entityvector.begin()
				;iter != this->blocks[i].entityvector.end();++iter)
			{
				dynamic_cast<Entity*>(*iter)->sprite.setPosition(offset * 3, -offset * 3);
				offset++;
			}
		}
	}
}


void ChessBoard_Client::onNotify(Entity* entity_, MVCEvent event)
{
	if (event == MVCEvent::PLANEMOVE_ONBOARD)
	{
		if (dynamic_cast<Plane_Client*>(entity_)->lastpos != 0)
		{
			this->blocks[dynamic_cast<Plane_Client*>(entity_)->lastpos - 1].PopFromQueue(entity_);
		}
		this->blocks[dynamic_cast<Plane_Client*>(entity_)->pos - 1].PushToQueue(entity_);
		this->blocks[dynamic_cast<Plane_Client*>(entity_)->pos - 1].judgehit(dynamic_cast<Plane_Client*>(entity_));

	}
}
void block_Client::judgehit(Plane_Client* plane_)
{
	if (entityvector.size() >= 2)
	{
		for (std::list<Entity*>::iterator iter = entityvector.begin();iter != entityvector.end();)
		{
			if (dynamic_cast<Plane_Client*>(*iter))
			{
				if (dynamic_cast<Plane_Client*>(*iter)->PPU != plane_->PPU)
				{
					dynamic_cast<Plane_Client*>(*iter)->Init();
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
void block_Client::PushToQueue(Entity* entity_)
{
	this->entityvector.push_back(entity_);
}

void block_Client::PopFromQueue(Entity* entity_)
{
	this->entityvector.remove(entity_);
}

