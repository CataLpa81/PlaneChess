#pragma once

#include<SFML/Network.hpp>
#include<iostream>
#include"Plane_Client.h"
#include"NetWork.h"


class Client
{
public:
	static Client* Instance()
	{
		static Client* Instance = new Client();
		return Instance;
	}
	sf::TcpSocket socket;
	sf::Packet packet;
	sf::Clock clock;
	void Run();
	void processDICE(sf::Packet&);
	void processPLANE(sf::Packet&);

	void processSTART(sf::Packet&);
	void processSETNUMBER(sf::Packet&);
	void processSETNAME(sf::Packet&);
private:
	Client() {}
};