#include "Character.h"
#include <iostream>
#include <sstream>

Character::Character(void) : 
	sf::Drawable(), _TexturePtr(new sf::Texture()), _SpritePtr(new sf::Sprite())
{

}


Character::~Character(void)
{
	sf::Drawable::~Drawable();
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

	_AnimationManagerPtr->update(elapsed);
}

void Character::load()
{
	 if (_TexturePtr->loadFromFile("Bilder/Gra-Fisch_schwimm.png"))
	 {
		 _TexturePtr->setSmooth(true);
		 _SpritePtr->setTexture(*_TexturePtr);
		 _SpritePtr->setPosition(0,250);
		 _SpritePtr->setScale(0.20f, 0.20f);

		 _AnimationManagerPtr = std::unique_ptr<AnimationManager>(new AnimationManager(_SpritePtr, sf::IntRect(0, 0, 595, 421)));

 		 std::shared_ptr<Animation> tempAnimation(new Animation(_SpritePtr, 500));
		 tempAnimation->addFrame(sf::IntRect(0, 0, 595, 421));
		 tempAnimation->addFrame(sf::IntRect(0, 421, 595, 421));

		 _AnimationManagerPtr->addAnimation("Schwimmen", tempAnimation);
		 _AnimationManagerPtr->startAnimation("Schwimmen");
	 }
}

void Character::draw (sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(*_SpritePtr);
}

bool Character::collisionPiranha(std::list<std::shared_ptr<Piranha>> &piranhaList)
{
	return false;
}

 const sf::Vector2f &Character::getPosition() const
{
	return _SpritePtr->getPosition();
}

const std::shared_ptr<sf::Sprite > Character::getSprite() const
 {
	 return _SpritePtr;
 }

 std::shared_ptr<BlasenAttacke> Character::getAttack()
 {
	 static sf::Clock clock;
	 sf::Time time = clock.getElapsedTime();

	std::shared_ptr<BlasenAttacke> blasenAttack(nullptr);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && time.asSeconds() >= 0.5f)
	{
		blasenAttack = std::shared_ptr<BlasenAttacke>(new BlasenAttacke);

		sf::Vector2f posi = this->getPosition();
		posi.y += 20;

		blasenAttack->load(posi);

		clock.restart();
	}

	return blasenAttack;
 }