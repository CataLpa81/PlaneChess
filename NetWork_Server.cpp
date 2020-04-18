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
		std::thread* t = new std::thread(&Server::Receive, this, client);
	}


}

void Server::Receive(sf::TcpSocket* ts)
{
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
			std::cout << "Server recivedPPU" << std::endl;
			processDICE(packet, ts);
			break;
		case PLANE:
			ts->receive(packet);
			std::cout << "Server recivedPPU" << std::endl;
			processPLANE(packet, ts);
			break;
		default:
			break;
		}




	}

}

void Server::SendPPU(sf::TcpSocket* ts)
{
}

void Server::processDICE(sf::Packet& packet, sf::TcpSocket* ts)
{
	int dicenumber;
	packet >> dicenumber;

	sf::Packet packet_;
	packet_ << dicenumber;
	for (sf::TcpSocket* socket : SocketSet)
	{
		if (socket != ts)
		{
			sf::Uint32 data = 'DICE';
			socket->send(&data, sizeof(Uint32));
			socket->send(packet);
			std::cout << "Server SendPPU" << std::endl;
		}

	}

}

void Server::processPLANE(sf::Packet& packet, sf::TcpSocket* ts)
{
	sf::Uint8 planenumber;
	packet >> planenumber;

	sf::Packet packet_;
	packet_ << planenumber;
	for (sf::TcpSocket* socket : SocketSet)
	{
		if (socket != ts)
		{
			sf::Uint32 data = 'PLNE';
			socket->send(&data, sizeof(Uint32));
			socket->send(packet_);
		}

	}
}