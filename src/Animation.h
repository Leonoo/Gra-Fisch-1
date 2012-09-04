#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Animation
{
public:
	Animation(std::shared_ptr<sf::Sprite> & spritePtr, sf::Int32 frameDuration);
	virtual ~Animation(void);

	void start();

	void update(sf::Time & elapsed);
	void addFrame(const sf::IntRect & frameRect);
	void setFrameDuration(sf::Int32 & duration);
	void setSprite(std::shared_ptr<sf::Sprite> spritePtr);

private:
	void SetFrame(sf::IntRect & frame);

	std::shared_ptr<sf::Sprite> _SpritePtr;
	std::vector<sf::IntRect> _FrameList;
	sf::Int32 _FrameDuration;

	sf::Time _Past;

	unsigned int _CurrentFrameIndex;
};

