#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <list>


#include "Piranha.h"
#include "BlasenAttacke.h"
#include "AnimationManager.h"

class Character : public sf::Drawable
{
public:
	Character(void);
	virtual ~Character(void);

	void load();
	void update(sf::Time &elapsed);
	virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const;
	bool collisionPiranha(std::list<std::shared_ptr<Piranha>> &piranhaList);

	const sf::Vector2f &getPosition() const;
	const std::shared_ptr<sf::Sprite > getSprite() const;

	std::shared_ptr<BlasenAttacke> getAttack();

private:
	void switchTexture();

	sf::Vector2f _OldPosition;
	sf::Time _Past;
	std::shared_ptr<sf::Texture> _TexturePtr;
	std::shared_ptr<sf::Sprite > _SpritePtr;

	std::unique_ptr<AnimationManager> _AnimationManagerPtr;
};

