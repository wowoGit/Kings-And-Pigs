#include "SolidBoundaries.h"

void SolidBoundaries::handleCollisionWith(Unit* unit)
{
	//std::cout << "called/n";
	for (Object solidObj : this->getBoundaries())
	{
		if (unit->getHitBox().intersects(sf::FloatRect(solidObj.rect)))
		{
			double playerFromRight = abs(unit->getHitBox().left - (solidObj.rect.left + solidObj.rect.width));
			double playerFromLeft = abs((unit->getHitBox().left + unit->getHitBox().width) - solidObj.rect.left);


			double playerFromBot = abs(unit->getHitBox().top - (solidObj.rect.top + solidObj.rect.height));
			double playerFromTop = abs((unit->getHitBox().top + unit->getHitBox().height) - solidObj.rect.top);

			bool CollisionFromLeft = playerFromLeft < playerFromRight ? true : false;
			bool CollisionFromTop = playerFromTop < playerFromBot ? true : false;

			double magnitudeX = CollisionFromLeft ? playerFromLeft : playerFromRight;
			double magnitudeY = CollisionFromTop ? playerFromTop : playerFromBot;
			if (magnitudeX < magnitudeY)
			{
				if (CollisionFromLeft)
				{
					unit->setPosition(solidObj.rect.left - unit->getGlobalBounds().width + unit->getHitBoxOffsetX(), unit->getGlobalBounds().top);
					unit->setHitBoxPos(solidObj.rect.left - unit->getHitBox().width, unit->getHitBox().top);
					//std::cout << "Collision from left " << std::endl;
				}
				else
				{
					unit->setPosition(solidObj.rect.left + solidObj.rect.width - unit->getHitBoxOffsetX(), unit->getGlobalBounds().top);
					unit->setHitBoxPos(solidObj.rect.left + solidObj.rect.width, unit->getHitBox().top);
					//std::cout << "Collision from right " << std::endl;
				}
				unit->resetVelocityX();
			}
			else
			{
				if (CollisionFromTop)
				{
					unit->setPosition(unit->getGlobalBounds().left, solidObj.rect.top - unit->getGlobalBounds().height + unit->getHitBoxOffsetY());
					unit->setHitBoxPos(unit->getHitBox().left, solidObj.rect.top - unit->getHitBox().height);
					unit->resetVelocityY();
					unit->resetOnGround();


					//std::cout << solidObj.rect.top << std::endl;
				}
				else
				{
					unit->setPosition(unit->getGlobalBounds().left, solidObj.rect.top + solidObj.rect.height - unit->getHitBoxOffsetY());
					unit->setHitBoxPos(unit->getHitBox().left, solidObj.rect.top + solidObj.rect.height);
					//std::cout << "Collision from Bot " << std::endl;
					unit->resetVelocityY();
				}
			}
		}


	}
}
