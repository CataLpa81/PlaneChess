#include"InputBox.h"
#include<iostream>

extern sf::RenderWindow window;

void InputBox::Input(Event event)
{

	if (isCursorOut&&!isSelected)
		if (event.type == Event::MouseMoved
			&& this->hitbox.contains((sf::Vector2f)sf::Mouse::getPosition(window)))
		{
			cursor.loadFromSystem(sf::Cursor::Text);
			window.setMouseCursor(cursor);
			isCursorOut = false;
		}
		
	if(!isCursorOut)
		{
			if (event.type == Event::MouseButtonReleased
				&& event.mouseButton.button == sf::Mouse::Left
				)
			{
				if (this->hitbox.contains((sf::Vector2f)sf::Mouse::getPosition(window)))
				{
					this->isSelected = true;
				}
				else
				{
					this->isSelected = false;
				}

			}
			if (event.type == Event::MouseButtonReleased
				&& event.mouseButton.button == sf::Mouse::Right
				)
			{
				if (!this->hitbox.contains((sf::Vector2f)sf::Mouse::getPosition(window)))
				{
					this->isSelected = false;
				}
			}



			if (event.type == Event::MouseMoved
				&& !this->hitbox.contains((sf::Vector2f)sf::Mouse::getPosition(window)))
			{
				cursor.loadFromSystem(sf::Cursor::Arrow);
				window.setMouseCursor(cursor);
				if(!isSelected)
				isCursorOut = true;
			}

			if (isSelected)
			{
				if (event.type == sf::Event::TextEntered)
				{
					if (type == FULL)
					{
						
							if (event.text.unicode != 8 && InputContent.getSize() < LengthMax)
							{
								if (event.text.unicode >= InputRangeLower && event.text.unicode <= InputRangeUpper)
								{
									InputContent += event.text.unicode;
								}
							}
							else if (InputContent.getSize() > 0 && event.text.unicode == 8)
							{

								sf::Uint32 s;
								s = *(InputContent.end() - 1);
								InputContent.erase(InputContent.getSize() - 1, 1);
							}
							text.setString(InputContent);
						
						
					}
					else if (type == HALF && event.text.unicode <= 0x00FF)
					{
						
							if (event.text.unicode != 8 && InputContent.getSize() < LengthMax)
							{
								if (event.text.unicode >= InputRangeLower && event.text.unicode <= InputRangeUpper)
								{
									InputContent += event.text.unicode;
								}
							}
							else if (InputContent.getSize() > 0 && event.text.unicode == 8)
							{
								sf::Uint32 s;
								s = *(InputContent.end() - 1);
								InputContent.erase(InputContent.getSize() - 1, 1);
							}
							text.setString(InputContent);
						
					}

				}
			}
		}
	
}

void InputBox::Render()
{
	window.draw(this->sprite);
	text.setOrigin(text.getLocalBounds().width / 2, textSize / 2);
	if (InputContent.getSize() > 8);
	{

		text.setCharacterSize(textSize - 5);
	}
	if (InputContent.getSize() <= 8)
	{
		text.setCharacterSize(textSize);
	}
	window.draw(text);
	if (isSelected && InputContent.getSize() < 1)
	{
		if (clock.getElapsedTime().asMilliseconds() > 500)
		{
			isDisplaySign = !isDisplaySign;
			clock.restart();
		}
		if (isDisplaySign)
			window.draw(this->Signsprite);
	}
}

void InputBox::SetPosition(int x, int y)
{
	this->sprite.setPosition(x, y);
	this->text.setPosition(x, y);
	this->hitbox = sprite.getGlobalBounds();

	this->Signsprite.setPosition(x, y);

}

sf::String InputBox::GetContent()
{
	return this->InputContent;
}




void ChatInputBox::Input(Event event)
{

	if (isCursorOut && !isSelected)
		if (event.type == Event::MouseMoved
			&& this->hitbox.contains((sf::Vector2f)sf::Mouse::getPosition(window)))
		{
			cursor.loadFromSystem(sf::Cursor::Text);
			window.setMouseCursor(cursor);
			isCursorOut = false;
		}

	if (!isCursorOut)
	{
		if (event.type == Event::MouseButtonReleased
			&& event.mouseButton.button == sf::Mouse::Left
			)
		{
			if (this->hitbox.contains((sf::Vector2f)sf::Mouse::getPosition(window)))
			{
				this->isSelected = true;
			}
			else
			{
				this->isSelected = false;
			}

		}
		if (event.type == Event::MouseButtonReleased
			&& event.mouseButton.button == sf::Mouse::Right
			)
		{
			if (!this->hitbox.contains((sf::Vector2f)sf::Mouse::getPosition(window)))
			{
				this->isSelected = false;
			}
		}



		if (event.type == Event::MouseMoved
			&& !this->hitbox.contains((sf::Vector2f)sf::Mouse::getPosition(window)))
		{
			cursor.loadFromSystem(sf::Cursor::Arrow);
			window.setMouseCursor(cursor);
			if (!isSelected)
				isCursorOut = true;
		}

		if (isSelected)
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode != 8 && InputContent.getSize() < LengthMax)
				{
						
						InputContent += event.text.unicode;
						InputContentTrans += event.text.unicode;
				}
				else if (InputContent.getSize() > 0 && event.text.unicode == 8)
				{

					InputContent.erase(InputContent.getSize() - 1, 1);

					InputContentTrans.erase(InputContentTrans.getSize() - 1, 1);
				}
				text.setString(InputContent);
				if (text.getLocalBounds().width > 460)
				{
					InputContent.insert(InputContent.getSize() - 1, '\n' );
				}
				text.setString(InputContent);
			}
		}
	}
}

void ChatInputBox::Render()
{
	window.draw(this->sprite);
	text.setOrigin(0,0);

	window.draw(text);
	if (isSelected && InputContent.getSize() < 1)
	{
		if (clock.getElapsedTime().asMilliseconds() > 500)
		{
			isDisplaySign = !isDisplaySign;
			clock.restart();
		}
		if (isDisplaySign)
			window.draw(this->Signsprite);
	}
}

void ChatInputBox::SetPosition(int x, int y)
{
	this->sprite.setPosition(x, y);
	this->text.setPosition(x,y);
	this->hitbox = sprite.getGlobalBounds();

	this->Signsprite.setPosition(x, y);

}

sf::String ChatInputBox::GetContent()
{
	return this->InputContentTrans;
}

void ChatInputBox::Clear()
{
	this->InputContent.clear();
	this->InputContentTrans.clear();
	this->text.setString(InputContent);
}




void Lable::SetPosition(int x, int y)
{
	this->sprite.setPosition(x, y);
	this->text.setPosition(x, y);

}

sf::String Lable::GetContent()
{
	return this->InputContent;
	
}

void Lable::SetContent(sf::String s)
{
	this->InputContent = s;
	this->text.setString(InputContent);
}

void Lable::Render()
{
	window.draw(this->sprite);
	text.setOrigin(text.getLocalBounds().width / 2, textSize/2);
	if(InputContent.getSize() > 8);
	{
		text.setCharacterSize(textSize - 8);
	}
	if(InputContent.getSize()<=8)
	{
		text.setCharacterSize(textSize);
	}
	window.draw(text);
}

void Lable::SetScale(double s)
{
	this->sprite.setScale(s, s);
	this->text.setScale(s, s);
	
}