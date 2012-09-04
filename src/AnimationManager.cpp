#include "AnimationManager.h"

AnimationManager::AnimationManager(std::shared_ptr<sf::Sprite> & spritePtr, sf::IntRect & defaultFrame)
{
	setSprite(spritePtr);
	setDefaultFrame(defaultFrame);
}

AnimationManager::~AnimationManager(void)
{
}

void AnimationManager::startAnimation(sf::String name)
{
	auto mapIterator = m_AnimationMap.find(name);
	if (mapIterator != m_AnimationMap.end())
	{
		m_CurrentAnimation = mapIterator->second;
		m_CurrentAnimation->start();
	}
}

void AnimationManager::stopAnimation()
{
	m_CurrentAnimation = nullptr;

	m_SpritePtr->setTextureRect(m_DefaultFrame);
}

void AnimationManager::update(sf::Time & elapsed)
{
	if (m_CurrentAnimation != nullptr)
	{
		m_CurrentAnimation->update(elapsed);
	}
}

void AnimationManager::addAnimation(sf::String name, std::shared_ptr<Animation> animationPtr)
{
	m_AnimationMap[name] = animationPtr;
}

void AnimationManager::removeAnimation(sf::String name)
{
	m_AnimationMap.erase(name);
}

void AnimationManager::setSprite(std::shared_ptr<sf::Sprite> & spritePtr)
{
	m_SpritePtr = spritePtr;
}
void AnimationManager::setDefaultFrame(sf::IntRect & frame)
{
	m_DefaultFrame = frame;
	stopAnimation();
}