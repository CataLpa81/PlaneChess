#include"ChatRoom.h"
#include<iostream>
#include"Audio.h"

extern sf::Mutex mutex;
extern sf::RenderWindow window;

void ChatRoom::setPosition(int x, int y)
{
	this->sprite.setPosition(x, y);
	this->Inputbox.SetPosition(x+5, y + (this->texture.getSize().y - 100));
	this->BS.setPosition(x + this->texture.getSize().x-50, y + this->texture.getSize().y-30);

}

void ChatRoom::addContent(sf::String s)
{
	static float height=0;
	sf::String temp;
	sf::Text t;
	t.setFont(font);
	t.setCharacterSize(15);
	t.setFillColor(Color(0, 0, 0));

	for (wchar_t a : s)
	{
		temp += a;
		t.setString(temp);
		if (t.getGlobalBounds().width > 460)
		{
			temp.insert(temp.getSize() - 1, '\n');
		}
	}
	t.setString(temp);

	height += 1.5*t.getLocalBounds().height;
	ContentList.push_back(t);
	AudioManager::Instance()->Play("msg");
	while (height > (texture.getSize().y - 110))
	{
		height -= 1.5*ContentList.front().getLocalBounds().height;
		ContentList.pop_front();
	}
}

void ChatRoom::drawContent()
{
	float line = 0;
	mutex.lock();
	for (sf::Text t:ContentList)
	{
		t.setPosition(this->sprite.getPosition().x+10, 5+line);
		line += t.getLocalBounds().height*1.5;
		window.draw(t);
	}
	mutex.unlock();
}

void ChatRoom::Render()
{
	window.draw(this->sprite);
	Inputbox.Render();
	drawContent();
	this->BS.Render();
}

void ChatRoom::Input(Event event)
{
	this->Inputbox.Input(event);
	this->BS.Input(event);
}