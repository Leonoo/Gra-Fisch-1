#include "Animation.h"

Animation::Animation(std::shared_ptr<sf::Sprite> & spritePtr, sf::Int32 frameDuration)
{
	setSprite(spritePtr);
	setFrameDuration(frameDuration);
}

Animation::~Animation(void)
{
}

void Animation::start()
{
	_CurrentFrameIndex = 0;
	SetFrame(_FrameList[0]);
	_Past = sf::Time::Zero;
}

void Animation::update(sf::Time & elapsed)
{
	_Past += elapsed;

	if (_Past.asMilliseconds() > _FrameDuration)
	{
		_CurrentFrameIndex++;
		
		if (_CurrentFrameIndex >= _FrameList.size())
		{
			_CurrentFrameIndex = 0;
		}

		auto currentFrame = _FrameList[_CurrentFrameIndex];
		SetFrame(currentFrame);

		_Past = sf::Time::Zero;
	}
}

void Animation::addFrame(const sf::IntRect & frameRect)
{
	_FrameList.push_back(frameRect);
}

void Animation::setFrameDuration(sf::Int32 & duration)
{
	_FrameDuration = duration;
}

void Animation::setSprite(std::shared_ptr<sf::Sprite> spritePtr)
{
	_SpritePtr = spritePtr;
}

void Animation::SetFrame(sf::IntRect & frame)
{
	_SpritePtr->setTextureRect(frame);
}