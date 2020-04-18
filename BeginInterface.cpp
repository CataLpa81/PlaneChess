#include"BeginInterface.h"

BeginInterface::BeginInterface()
{
	this->texture.loadFromFile("./data/UI/start_bk.png");
	this->sprite.setTexture(texture);
	this->btnLG.setPosition(600, 550);
}

void BeginInterface::Render()
{
	window.draw(this->sprite);
	btnLG.Render();
}

void BeginInterface::Input(Event event)
{
	btnLG.Input(event);
}


NetGame1_Scence::NetGame1_Scence()
{
	this->texture.loadFromFile("./data/UI/NetGame1_Scence.png");
	this->sprite.setTexture(texture);
}


void NetGame1_Scence::Render()
{

}

void NetGame1_Scence::Input(Event event)
{

}

