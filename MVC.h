#pragma once
#include<set>


extern class Entity;

enum MVCEvent
{
	DICETIME,
	PLANETIME,

	PLANEMOVE_ONBOARD,
};

class Observer
{
public:
	virtual ~Observer(){}
	virtual void onNotify(Entity* entity_,MVCEvent event) = 0;
};

class Subject
{
public:
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
protected:
	void notify(Entity* entity_,MVCEvent event);
private:
	std::set<Observer*> observers;
	
};