#include"NetWork_Client.h"




void Client::Run()
{
	socket.connect("localhost", 8888);
	std::cout << "Client launched" << std::endl;
	clock.restart();
}
