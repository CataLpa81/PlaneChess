#include"Button.h"
#include"Game.h"


void Button::InitTexture()
{
	TV.x = texture.getSize().x / 3;
	TV.y = texture.getSize().y;
	setTexture(1);
}

Button::Button(sf::String s)
{
	this->texture.loadFromFile(s);
	this->sprite.setTexture(texture);
	InitTexture();
	setOriginCenter();
}

void Button::setPosition(int x,int y)
{
	this->sprite.setPosition(x, y);
	this->hitbox = sprite.getGlobalBounds();
}

void Button::setOriginCenter()
{
	this->sprite.setOrigin(this->texture.getSize().x / 6, this->texture.getSize().y / 2);
}

void Button::Render()
{
	window.draw(this->sprite);
}


void Button::Input(Event event)
{
	if (event.type == Event::MouseButtonReleased
		&& event.mouseButton.button == sf::Mouse::Left
		)
	{
		if (this->hitbox.contains((sf::Vector2f)sf::Mouse::getPosition(window)))
		{
			OnRelese();
		}
		setTexture(IDLE);
		isPressed = false;
	}

	 if (event.type == Event::MouseButtonPressed
		&& event.mouseButton.button == sf::Mouse::Left
		&& this->hitbox.contains((sf::Vector2f)sf::Mouse::getPosition(window)))
	{
		setTexture(PRESS);
		OnPress();
		isPressed = true;
	}

	 if (isPressed == false)
	 {
		 if (event.type == Event::MouseMoved
			 && this->hitbox.contains((sf::Vector2f)sf::Mouse::getPosition(window)))
		 {
			 setTexture(MOVE);
			 OnMove();
		 }

		 if (event.type == Event::MouseMoved
			 && !this->hitbox.contains((sf::Vector2f)sf::Mouse::getPosition(window)))
		 {
			 setTexture(IDLE);
		 }
	 }
	 

}

void Button::setTexture(int frame)
{
	sf::Rect<int> TRect(Vector2i(TV.x*(frame-1),0), TV);
	this->sprite.setTextureRect(TRect);
}


void btnLocalGame::OnPress()
{
	
}

void btnLocalGame::OnRelese()
{
	GP = GameScence::LOCALGAME;
}


void btnNetGame::OnRelese()
{
	GP = GameScence::NETGAME1;
}


void btnNetGame::OnPress()
{
	
}


void btnCreateGame::OnRelese()
{
	GP = GameScence::NETGAME2;
}

void btnCreateGame::OnPress()
{

}

void btnJoinGame::OnPress()
{

}

void btnJoinGame::OnRelese()
{
	GP == GameScence::NETGAME3;
}

void btnStartGame::OnRelese()
{

}

void btnStartGame::OnPress()
{

}
