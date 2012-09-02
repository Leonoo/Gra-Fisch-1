#include "Character.h"
#include <iostream>
#include <sstream>

Character::Character(void) : _TexturePtr(new sf::Texture()), _SpritePtr(new sf::Sprite())
{

}


Character::~Character(void)
{

}

void Character::update(sf::Time &elapsed)
{
	_Past += elapsed;

	float Offset = 200.f * elapsed.asSeconds();
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		_SpritePtr->move(0, -Offset);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_SpritePtr->move(0, Offset);
	}

	_SpritePtr->move(Offset / 2.f, 0);

	if (_Past.asSeconds() >= 0.100f)
	{
		_Past = _Past.Zero;
		switchTexture();
	}
}

void Character::load()
{
	 if (_TexturePtr->loadFromFile("Ressourcen/Gra-Fisch_schwimm.png"))
	 {
		 _SpritePtr->setTexture(*_TexturePtr);
		 _SpritePtr->setPosition(0,250);
		 _SpritePtr->setScale(0.25, 0.25);
		 this->switchTexture();
	 }
}

void Character::draw(sf::RenderWindow &randerWindow)
{
	randerWindow.draw(*_SpritePtr);
}

 const sf::Vector2f &Character::getPosition() const
{
	return _SpritePtr->getPosition();
}

void Character::switchTexture()
{
	static bool hasSwitch;

	if (hasSwitch)
	{
		_SpritePtr->setTextureRect(sf::IntRect(0, 0, 595, 421));
		hasSwitch = false;
	}
	else
	{
		_SpritePtr->setTextureRect(sf::IntRect(0, 421, 595, 421));
		hasSwitch = true;
	}
}