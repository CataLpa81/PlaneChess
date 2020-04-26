#include"Scence.h"
#include"NetWork_Client.h"
#include"NetWork.h"





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


NetGame2_Scence::NetGame2_Scence()
{
	this->texture.loadFromFile("./data/UI/NetGame2_Scence.png");
	this->sprite.setTexture(texture);
	this->btnSG.setPosition(250, 650);
	tRED.loadFromFile("./data/UI/BIG_RED.png");
	sRED.setTexture(tRED);
	sRED.setOrigin(tRED.getSize().x / 2, tRED.getSize().y / 2);
	tGREEN.loadFromFile("./data/UI/BIG_GREEN.png");
	sGREEN.setTexture(tGREEN);
	sGREEN.setOrigin(tGREEN.getSize().x / 2, tGREEN.getSize().y / 2);
	tYELLOW.loadFromFile("./data/UI/BIG_YELLOW.png");
	sYELLOW.setTexture(tYELLOW);
	sYELLOW.setOrigin(tYELLOW.getSize().x / 2, tYELLOW.getSize().y / 2);
	tBLUE.loadFromFile("./data/UI/BIG_BLUE.png");
	sBLUE.setTexture(tBLUE);
	sBLUE.setOrigin(tBLUE.getSize().x / 2, tBLUE.getSize().y / 2);

	sRED.setPosition(1010, 178);
	sGREEN.setPosition(701, 178);
	sYELLOW.setPosition(1010, 556);
	sBLUE.setPosition(701, 556);

	Lgreen.SetPosition(701,335);
	Lred.SetPosition(1010, 335);
	Lyellow.SetPosition(1010, 712);
	Lblue.SetPosition(701, 712);
}


void NetGame2_Scence::Render()
{
	window.draw(this->sprite);
	this->btnSG.Render();
	if (GameManagerClient::instance()->planepool->redPlane_Clientpool.playerName != "null")
	{
		window.draw(this->sRED);
		Lred.SetContent(GameManagerClient::instance()->planepool->redPlane_Clientpool.playerName);
		Lred.Render();
	}
		
	if (GameManagerClient::instance()->planepool->greenPlane_Clientpool.playerName != "null")
	{
		window.draw(this->sGREEN);
		Lgreen.SetContent(GameManagerClient::instance()->planepool->greenPlane_Clientpool.playerName);
		Lgreen.Render();
	}
		
	if (GameManagerClient::instance()->planepool->bluePlane_Clientpool.playerName != "null")
	{
		window.draw(this->sBLUE);
		Lblue.SetContent(GameManagerClient::instance()->planepool->bluePlane_Clientpool.playerName);
		Lblue.Render();
	}
		
	if (GameManagerClient::instance()->planepool->yellowPlane_Clientpool.playerName != "null")
	{
		window.draw(this->sYELLOW);
		Lyellow.SetContent(GameManagerClient::instance()->planepool->yellowPlane_Clientpool.playerName);
		Lyellow.Render();
	}
		
}


void NetGame2_Scence::Input(Event event)
{
	this->btnSG.Input(event);
	
}


NetGame1_Scence::NetGame1_Scence()
{
	IB2 = new InputBox(4, 0x30, 0x39);
	this->texture.loadFromFile("./data/UI/NetGame1_Scence.png");
	this->sprite.setTexture(texture);
	this->btnJG.setPosition(600, 600);
	this->btnB.setPosition(100, 50);
	this->IB1.SetPosition(600, 339);
	this->IB2->SetPosition(600, 447);

	f.loadFromFile("./data/Fonts/qingyuan.ttc");
	t.setFont(f);
	t.setCharacterSize(50);
	t.setString(L"房间已满");
	t.setOrigin(t.getLocalBounds().width / 2, t.getLocalBounds().height / 2);
	t.setPosition(600, 700);
	Color c(0, 0, 0,255);
	t.setFillColor(c);

	f1.loadFromFile("./data/Fonts/qingyuan.ttc");
	t1.setFont(f1);
	t1.setCharacterSize(50);
	t1.setString(L"游戏已经开始");
	t1.setOrigin(t1.getLocalBounds().width / 2, t1.getLocalBounds().height / 2);
	t1.setPosition(600, 700);

	t1.setFillColor(c);

}


void NetGame1_Scence::Render()
{
	window.draw(this->sprite);
	this->btnJG.Render();
	this->btnB.Render();
	this->IB1.Render();
	this->IB2->Render();


	if (isFull)
		window.draw(t);
	if (isStart)
		window.draw(t1);

	if (c.getElapsedTime().asSeconds() > 3)
	{
		isFull = false;
		isStart = false;
	}
		
	
}

void NetGame1_Scence::Input(Event event)
{
	this->btnB.Input(event);
	this->btnJG.Input(event);
	this->IB1.Input(event);
	this->IB2->Input(event);
}

void NetGame1_Scence::DisPlayFULL()
{
	isFull = true;
	c.restart();

}

void NetGame1_Scence::DisPlaySTARTED()
{
	isStart = true;
	c.restart();

}

