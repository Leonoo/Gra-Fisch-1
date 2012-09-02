#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Character
{
public:
	Character(void);
	virtual ~Character(void);

	void load();
	void update(sf::Time &elapsed);
	void draw(sf::RenderWindow &randerWindow);

	const sf::Vector2f &getPosition() const;

private:
	void switchTexture();

	sf::Time _Past;
	std::unique_ptr<sf::Texture> _TexturePtr;
	std::unique_ptr<sf::Sprite > _SpritePtr;
};

