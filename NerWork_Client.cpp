#include"NetWork_Client.h"




void Client::Run()
{
	socket.connect("localhost", 8888);
	std::cout << "Client launched" << std::endl;
	clock.restart();
	while (1)
	{
		if (clock.getElapsedTime().asMilliseconds() > 500)
		{
			SendPPU();
			std::cout << "Client Send PPU" << std::endl;
			RecivePPU();
			clock.restart();
		}
		
	}
}

void Client::SendPPU()
{
	packet << PlanePool::instance()->blueplanepool << PlanePool::instance()->redplanepool
		<< PlanePool::instance()->yellowplanepool << PlanePool::instance()->greenplanepool;
	socket.send(packet);
	packet.clear();
}

void Client::RecivePPU()
{
	socket.receive(packet);
	packet >> PlanePool::instance()->blueplanepool >> PlanePool::instance()->redplanepool
		>> PlanePool::instance()->yellowplanepool >> PlanePool::instance()->greenplanepool;
	std::cout << "Client Recived PPU" << std::endl;
}