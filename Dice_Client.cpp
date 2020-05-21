#include"Dice_Client.h"
#include<iostream>
#include"Audio.h"


int Dice_Client::createNumber()
{
	srand((int)time(NULL));
	int number = rand() % 6 + 1;
	std::cout << "number = " << number << std::endl;
	Number = number;
	return number;
}

Dice_Client::Dice_Client()
{
	this->texture.loadFromFile("./data/Entity/Dice.png");
	this->sprite.setTexture(this->texture);
	this->x = 50 + 300;
	this->y = 100 + 300;
	this->sprite.setOrigin(16, 17);
	this->sprite.setPosition(x, y);
	this->hitbox = this->sprite.getGlobalBounds();
	AnimCTL.AddAnimation(new Animation("dicing", Vector2i(32, 34), 7, 9, &sprite));
	AnimCTL.AddAnimation(new Animation("one", Vector2i(32, 34), 1, 1, &sprite));
	AnimCTL.AddAnimation(new Animation("two", Vector2i(32, 34), 2, 2, &sprite));
	AnimCTL.AddAnimation(new Animation("three", Vector2i(32, 34), 3, 3, &sprite));
	AnimCTL.AddAnimation(new Animation("four", Vector2i(32, 34), 4, 4, &sprite));
	AnimCTL.AddAnimation(new Animation("five", Vector2i(32, 34), 5, 5, &sprite));
	AnimCTL.AddAnimation(new Animation("six", Vector2i(32, 34), 6, 6, &sprite));
	AnimCTL.SwitchAnimation("one");
}

void Dice_Client::input(sf::Event& event)
{
	if (doDice_Client)
	{
		if (event.type == Event::MouseButtonReleased
			&& event.mouseButton.button == sf::Mouse::Left
			&& this->hitbox.contains((sf::Vector2f)sf::Mouse::getPosition(window)))
		{
			AnimCTL.SwitchAnimation("dicing");
			AudioManager::Instance()->Play("dice");
			clock.restart();
			createNumber();
			doDice_Client = false;
			//给观察这发送消息，轮到飞机的操作时间
			this->notify(this, MVCEvent::PLANETIME);

			sf::Uint32 data = DICE;
			Client::Instance()->socket.send(&data, sizeof(Uint32));

			Packet packet;
			packet << this->Number;
			//把骰子的结果发送给服务端
			Client::Instance()->socket.send(packet);
		}
	}

}
void Dice_Client::input(sf::Packet& packet)
{
	AnimCTL.SwitchAnimation("dicing");
	clock.restart();
	//从服务端接受骰子的结果
	packet >> this->Number;
	doDice_Client = false;
	std::cout << "number = " << this->Number << std::endl;
	//给观察这发送消息，轮到飞机的操作时间
	this->notify(this, MVCEvent::PLANETIME);
}

void Dice_Client::Rander()
{
	window.draw(this->sprite);
}

void Dice_Client::SetNumberAnim()
{
	switch (Number)
	{
	case 1:
		AnimCTL.SwitchAnimation("one");
		break;
	case 2:
		AnimCTL.SwitchAnimation("two");
		break;
	case 3:
		AnimCTL.SwitchAnimation("three");
		break;
	case 4:
		AnimCTL.SwitchAnimation("four");
		break;
	case 5:
		AnimCTL.SwitchAnimation("five");
		break;
	case 6:
		AnimCTL.SwitchAnimation("six");
		break;
		break;
	default:
		break;
	}
}

void Dice_Client::Update()
{
	AnimCTL.currentAnim->Update();
	if (clock.getElapsedTime().asMilliseconds() > 500)
	{
		SetNumberAnim();
		doDice_Client = true;
	}
}