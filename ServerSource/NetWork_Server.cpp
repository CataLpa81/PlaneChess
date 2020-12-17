#include"NetWork_Server.h"
using namespace sf;

void Server::Run()
{

	if (listener.listen(8888) != sf::Socket::Done) {}
	std::cout << "Server Launched,port on 8888" << std::endl;
	while (1)
	{
		sf::TcpSocket* client = new sf::TcpSocket;
		listener.accept(*client);
		this->SocketSet.insert(client);
		std::cout << "Get Client from " << client->getRemoteAddress() << std::endl;
		Player* player = new Player();
		player->socket = client;
		std::thread* t = new std::thread(&Server::Receive, this, player);

	}


}

void Server::Receive(Player* player)
{
	
	TcpSocket* ts = player->socket;
	while (1)
	{
		sf::Packet packet;
		sf::Uint32* data = (sf::Uint32*)malloc(sizeof(sf::Uint32));
		std::size_t recived;
		sf::Socket::Status status = ts->receive(data, sizeof(sf::Uint32), recived);
		if(status==sf::Socket::Status::Done)
		switch (*data)
		{
		case DICE:
			ts->receive(packet);
			std::cout << "Server recived DICE" << std::endl;
			processDICE(packet, player);
			break;
		case PLANE:
			ts->receive(packet);
			std::cout << "Server recived PLANE" << std::endl;
			processPLANE(packet, player);
			break;
		case HELLO:
			ts->receive(packet);
			std::cout << "Server recived HELLO" << std::endl;
			processHELLO(packet, player);
			break;
		case START:
			std::cout << "Server recived START" << std::endl;
			processSTART(player);
			break;
		case CHAT:
			ts->receive(packet);
			std::cout << "Server recived CHAT" << std::endl;
			processCHAT(packet,player);
			break;
		case EXIT:
			processEXIT(player);
			return;
			break;
		default:
			break;
		}
		else if (status == sf::Socket::Status::Disconnected)
		{
			processEXIT(player);
			return;
		}
		
	}

}

void Server::SendPPU(sf::TcpSocket* ts)
{

}

void Server::processDICE(sf::Packet& packet, Player* player)
{
	
	sf::TcpSocket* ts = player->socket;
	sf::Uint8 dicenumber;
	packet >> dicenumber;

	sf::Packet packet_;
	packet_ << dicenumber;
	std::cout << dicenumber<<std::endl;
	for (Player* p:player->belongTo->Players)
	{
		if ( p->socket!= ts&&p->socket!=nullptr)
		{
			sf::Uint32 data = CDICE;
			p->socket->send(&data, sizeof(Uint32));
			p->socket->send(packet);
		}

	}
	std::cout << "player" << player->name.toAnsiString() << "dicing" << std::endl;

}

void Server::processPLANE(sf::Packet& packet, Player* player)
{
	sf::TcpSocket* ts = player->socket;
	sf::Uint8 planenumber;
	packet >> planenumber;

	sf::Packet packet_;
	packet_ << planenumber;
	for (Player* p : player->belongTo->Players)
	{
		if (p->socket != ts&&p->socket!=nullptr)
		{
			sf::Uint32 data = CPLANE;
			p->socket->send(&data, sizeof(Uint32));
			p->socket->send(packet_);
		}

	}
	std::cout << "player" << player->name.toAnsiString() << "operate plane " <<planenumber<< std::endl;
}

void Server::processHELLO(sf::Packet& packet, Player* player)
{

	bool isExist = false;

	sf::TcpSocket* ts = player->socket;
	sf::Uint16 RoomNumber;
	sf::String name;
	packet >> RoomNumber >> name;

	player->name = name;

	for (std::map<sf::Uint16, GameRoom*>::iterator iter = RoomSet.begin();
		iter != RoomSet.end();++iter)
	{
		if (iter->first == RoomNumber)
		{
			iter->second->addPlayer(player);
			isExist = true;
			
			break;
		}
	}
	if (!isExist)
	{
		GameRoom* room=new GameRoom();
		room->roomID = RoomNumber;
		room->addPlayer(player);
		RoomSet.insert(std::pair<sf::Uint16,GameRoom*>(RoomNumber,room));
	}
	
	if (player->belongTo == nullptr)
		return;
	

	sf::Uint32 data = SETNUMBER;
	player->socket->send(&data, sizeof(sf::Uint32));
	sf::Packet _packet;
	_packet << player->planeNumber;
	player->socket->send(_packet);
	sf::Uint32 data2 = SETNAME;
	for (int i=0;i<4;i++)
	{
		if (player->belongTo->Players[i]->socket != nullptr)
		{

			player->belongTo->Players[i]->socket->send(&data2, sizeof(sf::Uint32));
			sf::Packet __packet;
			for (int j=0;j<4;j++)
			{
				__packet << player->belongTo->Players[j]->name;
			}
			player->belongTo->Players[i]->socket->send(__packet);
		}
	}


}


void Server::processEXIT(Player* player)
{
	if (player->belongTo != nullptr)
	{
		std::cout << player->name.toAnsiString() << " exit room " << player->belongTo->roomID << std::endl;
		player->belongTo->isFull = false;
		player->name = "null";
		sf::Uint32 data2 = SETNAME;
		for (int i = 0;i < 4;i++)
		{

			if (player->belongTo->Players[i]->socket != nullptr)
			{

				player->belongTo->Players[i]->socket->send(&data2, sizeof(sf::Uint32));
				sf::Packet __packet;
				for (int j = 0;j < 4;j++)
				{
					__packet << player->belongTo->Players[j]->name;
				}
				player->belongTo->Players[i]->socket->send(__packet);
			}
		}
		

		player->belongTo->Players[player->planeNumber]->isFill = false;
		if (player->belongTo->Players[0]->isFill == false &&
			player->belongTo->Players[1]->isFill == false &&
			player->belongTo->Players[2]->isFill == false &&
			player->belongTo->Players[3]->isFill == false)
		{
			std::cout << "room " << player->belongTo->roomID << " erased" << std::endl;
			RoomSet.erase(player->belongTo->roomID);
			
		}
		player->belongTo->Players[player->planeNumber] = new Player();
	}
	
	delete player->socket;
	delete player;

}

void Server::processSTART(Player* player)
{
	
	std::cout << "room " << player->belongTo->roomID << " start game" << std::endl;
	sf::Uint32 start = CSTART;

		if (player->belongTo->Players[0]->socket != nullptr)
			player->belongTo->Players[0]->socket->send(&start, sizeof(sf::Uint32));
			

		if (player->belongTo->Players[1]->socket != nullptr)
			player->belongTo->Players[1]->socket->send(&start, sizeof(sf::Uint32));
			

		if (player->belongTo->Players[2]->socket!=nullptr)
			player->belongTo->Players[2]->socket->send(&start, sizeof(sf::Uint32));

		if (player->belongTo->Players[3]->socket!=nullptr)
			player->belongTo->Players[3]->socket->send(&start, sizeof(sf::Uint32));
	
	player->belongTo->isStart = true;
}


void Server::processCHAT(sf::Packet& packet, Player* player)
{
	sf::String s;
	packet >> s;
	sf::String s2 = player->name +":"+s;

	sf::Packet _packet;
	sf::Uint32 data = CCHAT;
	_packet << s2;
	
	for (Player* p : player->belongTo->Players)
	{
		if (p->socket != nullptr)
		{
			p->socket->send(&data, sizeof(sf::Uint32));
			p->socket->send(_packet);
		}
			
	}
}

void GameRoom::addPlayer(Player* player)
{
	

	if (isFull)
	{
		sf::Uint32 f = FULL;
		player->socket->send(&f,sizeof(sf::Uint32));
		return;
	}

	if (isStart)
	{
		sf::Uint32 s = STARTED;
		player->socket->send(&s, sizeof(sf::Uint32));
		return;
	}
	
	for (int i = 0;i < 4;i++)
	{
		if (!Players[i]->isFill)
		{
			player->belongTo = this;
			player->planeNumber = i;
			player->isFill = true;
			delete Players[i];
			Players[i] = player;
			std::cout << player->name.toAnsiString()<< " Join room " <<player->belongTo->roomID<< std::endl;
			break;
		}
	}

	if (Players[0]->isFill&&Players[1]->isFill&&Players[2]->isFill&&Players[3]->isFill)
	{
		isFull = true;
	}


	sf::Uint32 s = JOIN;
	player->socket->send(&s, sizeof(sf::Uint32));
	return;

}



void Player :: init()
{
	this->name = "null";
	this->roomNumber = NULL;
	this->belongTo = nullptr;
	this->planeNumber = NULL;
}

int main()
{
	Server* s = Server::Instance();
	s->Run();
}

