#pragma once
#include<set>

enum MVCEvent
{
	DICETIME,
	PLANETIME,
};

class Observer
{
public:
	virtual ~Observer(){}
	virtual void onNotify(MVCEvent event) = 0;
};

class Subject
{
public:
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
protected:
	void notify(MVCEvent event);
private:
	std::set<Observer*> observers;
	
};