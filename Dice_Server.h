#pragma once
#pragma once
#include"Entity.h"
#include"animator.h"
#include"NetWork_Client.h"
#include"NetWork_Server.h"
class Dice_Server : public Entity, public Subject
{
public:
	//µ¥ÀýÄ£Ê½
	static Dice_Server* instance()
	{
		static Dice_Server* instance = new Dice_Server();
		return instance;
	}
	virtual void Update();
	virtual void Rander();
	int createNumber();
	void SetNumberAnim();
	bool doDice_Server = true;
	int Number;
	void input(sf::Event& event);
	Animator AnimCTL;
	Clock clock;

private:
	Dice_Server();
};
