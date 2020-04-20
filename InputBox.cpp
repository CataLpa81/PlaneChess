#include"InputBox.h"


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
							InputContent += event.text.unicode;
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
							InputContent += event.text.unicode;
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
	window.draw(text);
	if (isSelected&&InputContent.getSize()<1)
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
	this->text.setPosition(x - texture.getSize().x / 2, y - texture.getSize().y / 2);
	this->hitbox = sprite.getGlobalBounds();

	this->Signsprite.setPosition(x - texture.getSize().x / 2, y);

}

sf::String InputBox::GetContent()
{
	return this->InputContent;
}