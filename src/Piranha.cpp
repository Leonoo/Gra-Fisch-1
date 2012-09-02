#include "Piranha.h"

#include <iostream>
#include <sstream>

bool PixelPerfectTest(const sf::Sprite& Object1, const sf::Image& Image1, const sf::Sprite& Object2, const sf::Image& Image2, sf::Uint8 AlphaLimit);

std::shared_ptr<sf::Texture> Piranha::_TexturePtr(nullptr);
sf::Image Piranha::_Image;

Piranha::Piranha(void) : sf::Drawable(), _SpritePtr(new sf::Sprite())
{
}


Piranha::~Piranha(void)
{
	sf::Drawable::~Drawable();
}

void Piranha::update(sf::Time &elapsed)
{
	float Offset = 350.f * elapsed.asSeconds();
	
	_OldPosition = _SpritePtr->getPosition();

	_SpritePtr->move(Offset / 2.f, 0);
}

void Piranha::load(const sf::Vector2f &startPosition)
{
	if (Piranha::_TexturePtr == nullptr)
	{
		Piranha::_TexturePtr = std::shared_ptr<sf::Texture>(new sf::Texture);
		if (_TexturePtr->loadFromFile("Ressourcen/piranha.jpg"))
		{
			Piranha::_Image = _TexturePtr->copyToImage();
			Piranha::_Image.flipHorizontally();
			Piranha::_Image.createMaskFromColor(sf::Color::White);
			_TexturePtr->loadFromImage(Piranha::_Image);
		}
	}

	 if (Piranha::_TexturePtr != nullptr)
	 {
		_SpritePtr->setTexture(*_TexturePtr);
		_SpritePtr->setPosition(startPosition);
		_SpritePtr->setScale(0.10f, 0.10f);
	 }
}

void Piranha::draw (sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(*_SpritePtr);
}

bool Piranha::collisionBlasenAttacke(std::list<std::shared_ptr<BlasenAttacke>> &blasenAttackeList)
{
	for(auto item: blasenAttackeList)
	{
		if (PixelPerfectTest(*_SpritePtr, _Image, *(item->getSprite()), item->getImage(), 0x1))
		{
			_SpritePtr->setPosition(_OldPosition);
			return true;
		}
	}

	return false;
}

 const sf::Vector2f &Piranha::getPosition() const
{
	return _SpritePtr->getPosition();
}

 const std::shared_ptr<sf::Sprite > Piranha::getSprite() const
 {
	 return _SpritePtr;
 }

void Piranha::switchTexture()
{

}