#pragma once

#include<SFML/Network.hpp>
#include<set>
#include<thread>
#include<iostream>
#include"NetWork.h"
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
	int x;
	void Run();
	void Receive(sf::TcpSocket* TS);
	void SendPPU(sf::TcpSocket* ts);
	void processDICE(sf::Packet&, sf::TcpSocket* ts);
	void processPLANE(sf::Packet&, sf::TcpSocket* ts);
private:
	Server() {}
};