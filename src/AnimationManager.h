#pragma once
#include "Animation.h"
#include <map>

class AnimationManager
{
public:
	AnimationManager(std::shared_ptr<sf::Sprite> & spritePtr, sf::IntRect & defaultFrame);
	virtual ~AnimationManager(void);

	void startAnimation(sf::String name);
	void stopAnimation();

	void update(sf::Time & elapsed);

	void addAnimation(sf::String name, std::shared_ptr<Animation> animationPtr);
	void removeAnimation(sf::String name);

	void setSprite(std::shared_ptr<sf::Sprite> & spritePtr);
	void setDefaultFrame(sf::IntRect & frame);

private:
	std::map<sf::String, std::shared_ptr<Animation>> m_AnimationMap;
	std::shared_ptr<Animation> m_CurrentAnimation;

	sf::IntRect m_DefaultFrame;
	std::shared_ptr<sf::Sprite> m_SpritePtr;
};

