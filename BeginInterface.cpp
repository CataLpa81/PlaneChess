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