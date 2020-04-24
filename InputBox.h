#pragma once

#include<SFML/Graphics.hpp>
using namespace sf;

class Lable
{
public:
	Lable()
	{
		this->texture.loadFromFile("./data/UI/Lable.png");
		this->sprite.setTexture(this->texture);
		this->sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
		font1.loadFromFile("./data/Fonts/qingyuan.ttc");
		this->text.setCharacterSize(textSize);
		this->text.setFont(font1);
		this->text.setFillColor(Color(0, 0, 0, 255));
	}

	void SetPosition(int x, int y);
	sf::String GetContent();
	void SetContent(sf::String);
	void Render();
	void SetScale(double s);


private:
	int LengthMax = 12;
	int textSize = 25;

	Sprite sprite;
	Texture texture;

	sf::String InputContent;
	sf::Font font1;
	sf::Text text;

};


class InputBox
{
public:

	InputBox()
	{
		this->texture.loadFromFile("./data/UI/InputBox.png");
		this->sprite.setTexture(this->texture);
		this->sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

		this->Signtexture.loadFromFile("./data/UI/InputSign.png");
		this->Signsprite.setTexture(this->Signtexture);
		this->Signsprite.setOrigin(Signtexture.getSize().x / 2, Signtexture.getSize().y / 2);

		font1.loadFromFile("./data/Fonts/qingyuan.ttc");
		this->text.setCharacterSize(textSize);
		this->text.setFont(font1);
		this->text.setFillColor(Color(0, 0, 0, 255));
	}

	InputBox(int maxChar,int RangeLower,int RangeUpper, sf::Uint32 _type='FULL') :LengthMax(maxChar),InputRangeLower(RangeLower),InputRangeUpper(RangeUpper) {
		this->texture.loadFromFile("./data/UI/InputBox.png");
		this->sprite.setTexture(this->texture);
		this->sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
		this->Signtexture.loadFromFile("./data/UI/InputSign.png");
		this->Signsprite.setTexture(this->Signtexture);
		this->Signsprite.setOrigin(Signtexture.getSize().x / 2, Signtexture.getSize().y / 2);

		font1.loadFromFile("./data/Fonts/qingyuan.ttc");
		this->text.setCharacterSize(textSize);
		this->text.setFont(font1);
		this->text.setFillColor(Color(0, 0, 0, 255));
		if (_type == 'HALF')
			type = HALF;
		if (_type == 'FULL')
			type = FULL;
		
	}
	virtual void SetPosition(int x, int y);
	sf::String GetContent();
	void Input(Event);
	virtual void Render();
	enum {
		HALF,
		FULL,
	}type = FULL;

protected:
	bool isSelected = false;
	bool isDisplaySign = false;
	int LengthMax = 12;
	int textSize = 20;
	bool isCursorOut=true;
	
	sf::Clock clock;
	sf::Cursor cursor;
	sf::FloatRect hitbox;
	Sprite sprite;
	Texture texture;
	Sprite Signsprite;
	Texture Signtexture;
	sf::String InputContent;
	sf::Font font1;
	sf::Text text;

	int InputRangeLower=0x00000;
	int InputRangeUpper=0xFFFFF;

};

class ChatInputBox 
{
public:

	ChatInputBox()
	{
		this->texture.loadFromFile("./data/UI/ChatInput.png");
		this->sprite.setTexture(this->texture);
		this->sprite.setOrigin(0,0);

		this->Signtexture.loadFromFile("./data/UI/InputSign.png");
		this->Signsprite.setTexture(this->Signtexture);
		this->Signsprite.setOrigin(Signtexture.getSize().x / 2, 0);

		font1.loadFromFile("./data/Fonts/qingyuan.ttc");
		this->text.setCharacterSize(textSize);
		this->text.setFont(font1);
		this->text.setFillColor(Color(0, 0, 0, 255));
	}

	
	virtual void SetPosition(int x, int y);
	sf::String GetContent();
	void Input(Event);
	void Render();
	void Clear();

protected:
	bool isSelected = false;
	bool isDisplaySign = false;
	int LengthMax = 140;
	int textSize = 15;
	bool isCursorOut = true;

	sf::Clock clock;
	sf::Cursor cursor;
	sf::FloatRect hitbox;
	Sprite sprite;
	Texture texture;
	Sprite Signsprite;
	Texture Signtexture;
	sf::String InputContent;
	sf::String InputContentTrans;
	sf::Font font1;
	sf::Text text;

};