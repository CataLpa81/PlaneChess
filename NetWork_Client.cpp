#include"NetWork_Client.h"
#include"Game.h"

extern sf::Mutex mutex;

void Client::Run()
{
	socket.connect("localhost", 8888);
	std::cout << "Client launched" << std::endl;
	clock.restart();

	while (1)
	{
		sf::Packet packet;
		sf::Uint32* data = (sf::Uint32*)malloc(sizeof(sf::Uint32));
		std::size_t recived;
		socket.receive(data, sizeof(sf::Uint32), recived);
		switch (*data)
		{
		case CDICE:
			socket.receive(packet);
			processDICE(packet);
			break;
		case CPLANE:
			socket.receive(packet);
			processPLANE(packet);
			break;
		case CSTART:
			processSTART(packet);
			break;
		case SETNUMBER:
			socket.receive(packet);
			processSETNUMBER(packet);
			break;
		case SETNAME:
			socket.receive(packet);
			processSETNAME(packet);
			break;
		case CCHAT:
			socket.receive(packet);
			processCCHAT(packet);
			break;
		default:
			break;
		}
	}
}

void Client::processDICE(sf::Packet& packet)
{
	GameManagerClient::instance()->dice->input(packet);
}

void Client::processPLANE(sf::Packet& packet)
{
	GameManagerClient::instance()->planepool->currentpool->Input(packet, 
		GameManagerClient::instance()->dice->Number);
}

void Client::processSTART(sf::Packet& packet)
{
	GP = GameScence::NETGAME;
}

void Client::processSETNUMBER(sf::Packet& packet)
{
	sf::Uint8 number;
	packet >> number;
	switch (number)
	{
	case 0:
		GameManagerClient::instance()->Player = GameManagerClient::RED;
		break;
	case 1:
		GameManagerClient::instance()->Player = GameManagerClient::YELLOW;
		break;
	case 2:
		GameManagerClient::instance()->Player = GameManagerClient::BLUE;
		break;
	case 3:
		GameManagerClient::instance()->Player = GameManagerClient::GREEN;
		break;
	default:
		break;
	}

}


void Client::processSETNAME(sf::Packet& packet)
{
	sf::String REDname;
	sf::String YELLOWname;
	sf::String BLUEname;
	sf::String GREENname;
	packet >> REDname >> YELLOWname >> BLUEname >> GREENname;

	GameManagerClient::instance()->planepool->redPlane_Clientpool.playerName = REDname;
	GameManagerClient::instance()->planepool->yellowPlane_Clientpool.playerName = YELLOWname;
	GameManagerClient::instance()->planepool->bluePlane_Clientpool.playerName = BLUEname;
	GameManagerClient::instance()->planepool->greenPlane_Clientpool.playerName = GREENname;
}

void Client::processCCHAT(sf::Packet& packet)
{
	sf::String s;
	packet >> s;
	mutex.lock();
	ChatRoom::Instance()->addContent(s);
	mutex.unlock();
}
