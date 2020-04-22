#pragma once

#include<SFML/Network.hpp>
#include<set>
#include<map>
#include<thread>
#include<iostream>
#include"NetWork.h"

extern class GameRoom;
extern class Player;




class Server
{
public:
	static Server* Instance()
	{
		static Server* instance = new Server();
		return instance;
	}
	sf::TcpListener listener;
	std::set<sf::TcpSocket*> SocketSet;
	std::map<sf::Uint16, GameRoom> RoomSet;
	void Run();
	void Receive(Player* player);
	void SendPPU(sf::TcpSocket* ts);
	void processDICE(sf::Packet&, Player* player);
	void processPLANE(sf::Packet&, Player* player);
	void processHELLO(sf::Packet&, Player* player);
	void processEXIT( Player* player);
	void processSTART(Player* player);
	
private:
	Server() {}
};

class Player
{
public:
	Player() {
		init();
	}
	sf::TcpSocket* socket;
	sf::String name;
	sf::Uint16 roomNumber;
	GameRoom* belongTo;
	sf::Uint8 planeNumber;
	void init();
private:
};


class GameRoom
{
public:
	GameRoom()
	{
		for (int i = 0;i < 4;i++)
		{
			Players[i] = nullptr;
		}
	}
	sf::Uint16 roomID;
	Player* Players[4];
	void addPlayer(Player* player);
	bool isFull=false;
private:
};