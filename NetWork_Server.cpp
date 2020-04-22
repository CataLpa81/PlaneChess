#include"NetWork_Server.h"


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
		ts->receive(data, sizeof(sf::Uint32), recived);
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
		case EXIT:
			std::cout << "Server recived EXIT" << std::endl;
			processEXIT(player);
			break;
		case START:
			ts->receive(packet);
			std::cout << "Server recived START" << std::endl;
			processSTART(player);
			break;

		default:
			break;
		}
		
	}

}

void Server::SendPPU(sf::TcpSocket* ts)
{

}

void Server::processDICE(sf::Packet& packet, Player* player)
{
	sf::TcpSocket* ts = player->socket;
	int dicenumber;
	packet >> dicenumber;

	sf::Packet packet_;
	packet_ << dicenumber;
	for (Player* p:player->belongTo->Players)
	{
		if ( p->socket!= ts&&p->socket!=nullptr)
		{
			sf::Uint32 data = 'DICE';
			p->socket->send(&data, sizeof(Uint32));
			p->socket->send(packet);
			std::cout << "Server Send DICE" << std::endl;
		}

	}

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
			sf::Uint32 data = 'PLNE';
			p->socket->send(&data, sizeof(Uint32));
			p->socket->send(packet_);
		}

	}
}

void Server::processHELLO(sf::Packet& packet, Player* player)
{
	bool isExist = false;

	sf::TcpSocket* ts = player->socket;
	sf::Uint16 RoomNumber;
	sf::String name;
	packet >> RoomNumber >> name;
	player->roomNumber = RoomNumber;
	player->name = name;

	for (std::map<sf::Uint16, GameRoom>::iterator iter;
		iter != RoomSet.end();++iter)
	{
		if (iter->first == RoomNumber)
		{
			iter->second.addPlayer(player);
			isExist = true;
			break;
		}
	}
	if (!isExist)
	{
		GameRoom room;
		room.addPlayer(player);
		RoomSet.insert(std::pair<sf::Uint16,GameRoom>(RoomNumber,room));
	}
	
	for (Player* p : player->belongTo->Players)
	{
		if (p != nullptr)
		{
			sf::Uint32 data = SETNUMBER;
			p->socket->send(&data, sizeof(sf::Uint32));
			sf::Packet _packet;
			_packet << player->planeNumber;
			p->socket->send(_packet);


			sf::Uint32 data2 = SETNAME;

			p->socket->send(&data2, sizeof(sf::Uint32));
			sf::Packet __packet;
			for (Player* p : player->belongTo->Players)
			{
				if (p != nullptr)
				{
					__packet << p->name;
				}
				else if (p == nullptr)
				{
					__packet << "null";
				}
			}
			p->socket->send(__packet);
		}
	}

}


void Server::processEXIT(Player* player)
{
	player->belongTo->Players[player->planeNumber] = nullptr;
	if (player->belongTo->Players[0] == nullptr&&
		player->belongTo->Players[1] == nullptr&&
		player->belongTo->Players[2] == nullptr&&
		player->belongTo->Players[3] == nullptr)
	{
		RoomSet.erase(player->belongTo->roomID);
	}
	player->init();
	
}

void Server::processSTART(Player* player)
{
	for (Player* p : player->belongTo->Players)
	{
		if (p != nullptr)
		{
			sf::Uint32 data = START;
			p->socket->send(&data, sizeof(sf::Uint32));
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
	
	for (int i = 0;i < 4;i++)
	{
		if (Players[i]==nullptr)
		{
			player->belongTo = this;
			player->planeNumber = i;
			Players[i] = player;
			break;
		}
	}

	if (Players[0]!=nullptr&&Players[1] != nullptr&&Players[2] != nullptr&&Players[3] != nullptr)
	{
		isFull = true;
	}

}



void Player :: init()
{
	this->name.clear();
	this->roomNumber = NULL;
	this->belongTo = nullptr;
	this->planeNumber = NULL;
}

