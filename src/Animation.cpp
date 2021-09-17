#include "Animation.h"
#include <iostream>
Animation::Animation(InitAnimation& InitParameters)
{
	animSprite = InitParameters.targetSprite;
	frameWidth = InitParameters.frameWidth;
	frameHeight = InitParameters.frameHeight;
	
	animTexture.loadFromFile(InitParameters.texturePath);
	for (int i = 0; i < animTexture.getSize().x / frameWidth; i++)
	{
		frames.push_back(sf::IntRect(i * frameWidth + InitParameters.x, InitParameters.y, frameWidth, frameHeight));
		frames_flipped.push_back(sf::IntRect(i + frameWidth + InitParameters.x, InitParameters.y, -frameWidth, frameHeight));
	}
	currentFrame = frames.front();
	this->animSprite->setTexture(animTexture);
	this->animSprite->setTextureRect(currentFrame);
	animName = InitParameters.name;
	priority = InitParameters.priority;
}

sf::String Animation::getAnimName()
{
	return animName;
}

sf::Sprite* Animation::getCurrentFrame()
{
	return animSprite;
}

bool Animation::isFinished()
{
	return finished;
}

int Animation::getPriority()
{
	return priority;
}
