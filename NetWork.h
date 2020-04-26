#pragma once
#include<SFML/Network.hpp>
#include<iostream>
#include"Plane_Client.h"
#include"Dice_Client.h"
#include"GameManager.h"

static const sf::Uint32 DICE = 'DICE';
static const sf::Uint32 PLANE = 'PLNE';
static const sf::Uint32 CDICE = 'CDIC';
static const sf::Uint32 CPLANE = 'CPLE';


static const sf::Uint32 HELLO = 'HELO';
static const sf::Uint32 FULL = 'FULL';
static const sf::Uint32 EXIT = 'EXIT';
static const sf::Uint32 START = 'STRT';
static const sf::Uint32 CSTART = 'CSTR';
static const sf::Uint32 SETNUMBER = 'SNUM';
static const sf::Uint32 SETNAME = 'SNAM';

static const sf::Uint32 CHAT = 'CHAT';
static const sf::Uint32 CCHAT = 'CCHA';

static const sf::Uint32 JOIN = 'JOIN';
