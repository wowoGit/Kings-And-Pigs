#include "AnimationManager.h"

void AnimationManager::addLoopedAnimation(sf::Sprite* targetSprite, sf::String texturePath, float x, float y, float frameWidth, float frameHeight, sf::String name, int priority)
{
	InitAnimation InitParameters;
	InitParameters.targetSprite = targetSprite;
	InitParameters.texturePath = texturePath;
	InitParameters.x = x;
	InitParameters.y = y;
	InitParameters.frameWidth = frameWidth;
	InitParameters.frameHeight = frameHeight;
	InitParameters.name = name;
	InitParameters.priority = priority;
	Animation* anim = new LoopedAnimation(InitParameters);
	animVect.push_back(anim);

}
void AnimationManager::addOnetimeAnimation(sf::Sprite* targetSprite, sf::String texturePath, float x, float y, float frameWidth, float frameHeight, sf::String name, int priority)
{
	InitAnimation InitParameters;
	InitParameters.targetSprite = targetSprite;
	InitParameters.texturePath = texturePath;
	InitParameters.x = x;
	InitParameters.y = y;
	InitParameters.frameWidth = frameWidth;
	InitParameters.frameHeight = frameHeight;
	InitParameters.name = name;
	InitParameters.priority = priority;
	Animation* anim = new OnetimeAnimation(InitParameters);
	animVect.push_back(anim);

}

void AnimationManager::setCurrentAnimation(sf::String name)
{

	for (auto n : animVect)
	{
		if (n->getAnimName() == name)
		{
			if (currentAnimation == nullptr)
			{
				currentAnimation = n;
				return;
			}
			if (n->getPriority() <= currentAnimation->getPriority())
			{
				currentAnimation = n;
				return;
			}
			else
			{
				if (currentAnimation->isFinished())
				{
					currentAnimation = n;
					return;
				}
			}
		}
	}




	
}

sf::Sprite* AnimationManager::getCurrentFrame()
{
	return currentAnimation->getCurrentFrame();
}

void AnimationManager::runCurrentAnimation()
{
	currentAnimation->runAnimation();
}

bool AnimationManager::currentAnimationIsOver()
{
	return currentAnimation->isFinished();
}

AnimationManager::~AnimationManager()
{
	for (auto anim : animVect)
	{
		delete anim;
	}
}
