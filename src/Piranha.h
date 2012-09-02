#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <list>

#include "BlasenAttacke.h"

class Piranha : public sf::Drawable
{
public:
	Piranha(void);
	virtual ~Piranha(void);

	void load(const sf::Vector2f &startPosition);
	void update(sf::Time &elapsed);
	virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const;
	bool collisionBlasenAttacke(std::list<std::shared_ptr<BlasenAttacke>> &blasenAttackeList);

	const sf::Vector2f &getPosition() const;
	const std::shared_ptr<sf::Sprite > getSprite() const;

private:
	void switchTexture();

	sf::Vector2f _OldPosition;
	sf::Time _Past;
	std::shared_ptr<sf::Sprite> _SpritePtr;

	static std::shared_ptr<sf::Texture> _TexturePtr;
	static sf::Image _Image;
};

