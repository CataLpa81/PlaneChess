#pragma once
#include<SFML/Network.hpp>
#include<iostream>
#include"Plane.h"
#include"Dice_Client.h"

sf::Packet& operator <<(sf::Packet& packet, const Plane& p);

sf::Packet& operator >>(sf::Packet& packet, Plane& p);

sf::Packet& operator<<(sf::Packet& packet, const PlanePoolUnit& PPU);


sf::Packet& operator>>(sf::Packet& packet, PlanePoolUnit& PPU);
