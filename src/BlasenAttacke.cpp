#include "BlasenAttacke.h"

std::shared_ptr<sf::Texture> BlasenAttacke::_TexturePtr(nullptr);
sf::Image BlasenAttacke::_Image;

BlasenAttacke::BlasenAttacke(void) : sf::Drawable(), _SpritePtr(new sf::Sprite())
{
}


BlasenAttacke::~BlasenAttacke(void)
{
	sf::Drawable::~Drawable();
}

void BlasenAttacke::update(sf::Time &elapsed)
{
	float Offset = 150.f * elapsed.asSeconds();
	
	_SpritePtr->move(-Offset / 2.f, 0);
}

void BlasenAttacke::load(const sf::Vector2f &startPosition)
{
	if (BlasenAttacke::_TexturePtr == nullptr)
	{
		BlasenAttacke::_TexturePtr = std::shared_ptr<sf::Texture>(new sf::Texture);
		if (_TexturePtr->loadFromFile("Ressourcen/wasserblasen.png"))
		{
			BlasenAttacke::_Image = _TexturePtr->copyToImage();
			BlasenAttacke::_Image.createMaskFromColor(sf::Color::White);
			_TexturePtr->loadFromImage(BlasenAttacke::_Image);
		}
	}

	 if (BlasenAttacke::_TexturePtr != nullptr)
	 {
		 _SpritePtr->setTexture(*_TexturePtr);
		 _SpritePtr->setPosition(startPosition);
		 _SpritePtr->setScale(0.10f, 0.10f);
		 
	 }
}

void BlasenAttacke::draw (sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(*_SpritePtr);
}

 const sf::Vector2f &BlasenAttacke::getPosition() const
{
	return _SpritePtr->getPosition();
}

 const std::shared_ptr<sf::Sprite > BlasenAttacke::getSprite() const
 {
	 return _SpritePtr;
 }

 const sf::Image &BlasenAttacke::getImage() const
 {
	 return _Image;
 }

void BlasenAttacke::switchTexture()
{

}