#pragma once
#include"InputBox.h"
#include"Button.h"
#include<list>


class ChatRoom
{
public:
	static ChatRoom* Instance()
	{
		static ChatRoom* instance = new ChatRoom();
		return instance;
	}

	ChatInputBox Inputbox;
	void Input(Event event);
	void setPosition(int x,int y);
	void addContent(sf::String);
	void drawContent();
	void Render();
	


private:
	std::list<sf::Text> ContentList;
	ChatRoom() 
	{
		this->texture.loadFromFile("./data/UI/ChatBox.png");
		sprite.setTexture(texture);

		font.loadFromFile("./data/Fonts/qingyuan.ttc");
	}
	Texture texture;
	Sprite sprite;
	sf::Font font;
	btnSend BS;
};