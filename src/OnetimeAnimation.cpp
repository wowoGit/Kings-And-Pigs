#include "OnetimeAnimation.h"

void OnetimeAnimation::runAnimation()
{
	finished = false;
	animSprite->setTexture(animTexture);
	if (clock.getElapsedTime().asSeconds() >= 0.1f)
	{
		this->animSprite->setTextureRect(currentFrame);
		//this->currentFrame.top = frameHeight;
		this->currentFrame.left += frameWidth;
		if (currentFrame.left > animSprite->getTexture()->getSize().x - frameWidth)
		{
			currentFrame.left = animSprite->getTexture()->getSize().x - frameWidth;
			finished = true;
		}
		this->clock.restart();

	}
}
