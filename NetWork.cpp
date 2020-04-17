#include"NetWork.h"

sf::Packet& operator <<(sf::Packet& packet, const Plane& p)
{
	return packet << p.pos << p.lastpos << p.stepcount << p.currentpos << p.doFly;
}

sf::Packet& operator >>(sf::Packet& packet, Plane& p)
{
	return packet >> p.pos >> p.lastpos >> p.stepcount >> p.currentpos >> p.doFly;
}


sf::Packet& operator<<(sf::Packet& packet, const PlanePoolUnit& PPU)
{
	return packet << *PPU.plane[0] << *PPU.plane[1] << *PPU.plane[2] << *PPU.plane[3]
		<< PPU.fine << PPU.ready_num;
}

sf::Packet& operator>>(sf::Packet& packet, PlanePoolUnit& PPU)
{
	return packet >> *PPU.plane[0] >> *PPU.plane[1] >> *PPU.plane[2] >> *PPU.plane[3]
		>> PPU.fine >> PPU.ready_num;
}