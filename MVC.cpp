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

void Subject::notify(MVCEvent event)
{
	for (Observer* ob : observers)
	{
		ob->onNotify(event);
	}
}