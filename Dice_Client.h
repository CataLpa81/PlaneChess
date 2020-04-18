#pragma once
#include"Entity.h"
#include"animator.h"
#include"NetWork_Client.h"
#include"NetWork_Server.h"

class Dice_Client : public Entity, public Subject
{
public:
	//µ¥ÀýÄ£Ê½
	static Dice_Client* instance()
	{
		static Dice_Client* instance = new Dice_Client();
		return instance;
	}
	virtual void Update();
	virtual void Rander();
	int createNumber();
	void SetNumberAnim();

	bool doDice_Client = true;
	sf::Uint8 Number;
	void input(sf::Event& event);
	void input(sf::Packet& packet);
	Animator AnimCTL;
	Clock clock;

private:
	Dice_Client();
};
