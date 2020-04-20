#include"Scence.h"






BeginInterface::BeginInterface()
{
	this->texture.loadFromFile("./data/UI/start_bk.png");
	this->sprite.setTexture(texture);
	this->btnLG.setPosition(600, 550);
	this->btnNG.setPosition(600, 650);
}

void BeginInterface::Render()
{
	window.draw(this->sprite);
	btnLG.Render();
	btnNG.Render();
}

void BeginInterface::Input(Event event)
{
	btnLG.Input(event);
	btnNG.Input(event);
}


NetGame1_Scence::NetGame1_Scence()
{
	this->texture.loadFromFile("./data/UI/NetGame1_Scence.png");
	this->sprite.setTexture(texture);
	this->btnCG.setPosition(350, 700);
	this->btnJG.setPosition(880, 700);
}


void NetGame1_Scence::Render()
{
	window.draw(this->sprite);
	this->btnCG.Render();
	this->btnJG.Render();
}

void NetGame1_Scence::Input(Event event)
{
	this->btnCG.Input(event);
	this->btnJG.Input(event);
	
}


NetGame2_Scence::NetGame2_Scence()
{
	this->texture.loadFromFile("./data/UI/NetGame2_Scence.png");
	this->sprite.setTexture(texture);
	this->btnSG.setPosition(600, 600);
	this->IB1.SetPosition(600, 339);
	this->IB2.SetPosition(600, 447);
}


void NetGame2_Scence::Render()
{
	window.draw(this->sprite);
	this->btnSG.Render();
	this->IB1.Render();
	this->IB2.Render();
	
}

void NetGame2_Scence::Input(Event event)
{
	this->btnSG.Input(event);
	this->IB1.Input(event);
	this->IB2.Input(event);
}

