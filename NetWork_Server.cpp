#include"NetWork_Server.h"


void Server::Run()
{

	if (listener.listen(8888) != sf::Socket::Done) {}
	std::cout << "Server Launched,port on 8888" << std::endl;
	while (1)
	{
		sf::TcpSocket* client = new sf::TcpSocket;
		listener.accept(*client);
		std::cout << "Get Client from " << client->getRemoteAddress() << std::endl;
		std::thread* t=new std::thread(&Server::Receive,this,client);
	}
	
	
}

void Server::Receive(sf::TcpSocket* ts)
{
	while (1)
	{
		ts->receive(packet);
		packet >> PlanePool::instance()->blueplanepool >> PlanePool::instance()->redplanepool
			>> PlanePool::instance()->yellowplanepool >> PlanePool::instance()->greenplanepool;
		std::cout << "Server recivedPPU" << std::endl;
		SendPPU(ts);

		std::cout << "Server SendPPU" << std::endl;

	}
	
}

void Server::SendPPU(sf::TcpSocket* ts)
{
	packet << PlanePool::instance()->blueplanepool << PlanePool::instance()->redplanepool
		<< PlanePool::instance()->yellowplanepool << PlanePool::instance()->greenplanepool;
	ts->send(packet);
	packet.clear();
}