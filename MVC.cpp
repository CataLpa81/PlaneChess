#include<set>
#include"MVC.h"

void Subject::addObserver(Observer* observer)
{
	observers.insert(observer);
}

void Subject::removeObserver(Observer* observer)
{
	observers.erase(observer);
}

void Subject::notify(Entity* entity_,MVCEvent event)
{
	for (Observer* ob : observers)
	{
		ob->onNotify(entity_,event);
	}
}