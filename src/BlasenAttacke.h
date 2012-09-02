#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class BlasenAttacke : public sf::Drawable
{
public:
	BlasenAttacke(void);
	virtual ~BlasenAttacke(void);

	void load(const sf::Vector2f &startPosition);
	void update(sf::Time &elapsed);
	virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const;

	const sf::Vector2f &getPosition() const;
	const std::shared_ptr<sf::Sprite > getSprite() const;
	const sf::Image &getImage() const;

private:
	void switchTexture();

	sf::Time _Past;
	std::shared_ptr<sf::Sprite > _SpritePtr;

	static std::shared_ptr<sf::Texture> _TexturePtr;
	static sf::Image _Image;
};

