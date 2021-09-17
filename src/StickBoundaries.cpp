#include "StickBoundaries.h"

void StickBoundaries::handleCollisionWith(Unit* unit)
{
	for (Object solidObj : this->getBoundaries())
	{
		if (unit->getHitBox().intersects(sf::FloatRect(solidObj.rect)))
		{
			if (round(unit->getHitBox().top + unit->getHitBox().height) <= solidObj.rect.top+ solidObj.rect.height&&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				double unitFromRight = abs(unit->getHitBox().left - (solidObj.rect.left + solidObj.rect.width));
				double unitFromLeft = abs((unit->getHitBox().left + unit->getHitBox().width) - solidObj.rect.left);


				double unitFromBot = abs(unit->getHitBox().top - (solidObj.rect.top + solidObj.rect.height));
				double unitFromTop = abs((unit->getHitBox().top + unit->getHitBox().height) - solidObj.rect.top);

				bool CollisionFromLeft = unitFromLeft < unitFromRight ? true : false;
				bool CollisionFromTop = unitFromTop < unitFromBot ? true : false;

				double magnitudeX = CollisionFromLeft ? unitFromLeft : unitFromRight;
				double magnitudeY = CollisionFromTop ? unitFromTop : unitFromBot;
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
					else if (unit->getHitBox().top + unit->getHitBox().height / 2 < solidObj.rect.top)
					{
						unit->setPosition(unit->getGlobalBounds().left, solidObj.rect.top + solidObj.rect.height - unit->getHitBoxOffsetY());
						unit->setHitBoxPos(unit->getHitBox().left, solidObj.rect.top + solidObj.rect.height);
						//std::cout << "Collision from Bot " << std::endl;
						unit->resetVelocityY();
						unit->resetOnGround();
						
					}
				}
			}


		}
	}
}
