#pragma once
#include"Entity.h"
#include"animator.h"

class Dice : public Entity, public Subject
{
public:
	//µ¥ÀýÄ£Ê½
	static Dice* instance()
	{
		static Dice* instance = new Dice();
		return instance;
	}
	virtual void Update();
	virtual void Rander();
	int createNumber();
	void SetNumberAnim();
	bool dodice = true;
	int Number;
	void input(sf::Event& event);
	Animator AnimCTL;
	Clock clock;

private:
	Dice();
};
