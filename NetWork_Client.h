#pragma once

#include<SFML/Network.hpp>
#include<iostream>
#include"Plane.h"
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
	void SendPPU();
	void RecivePPU();
private:
	Client();
};