#include "InvisibleBoundaries.h"

void InvisibleBoundaries::handleCollisionWith(Unit* unit)
{
	for (Object invisObj : this->getBoundaries())
	{
		if (unit->getHitBox().intersects(sf::FloatRect(invisObj.rect)))
		{
			double unitFromRight = abs(unit->getHitBox().left - (invisObj.rect.left + invisObj.rect.width));
			double unitFromLeft = abs((unit->getHitBox().left + unit->getHitBox().width) - invisObj.rect.left);

			bool CollisionFromLeft = unitFromLeft < unitFromRight ? true : false;

			if (CollisionFromLeft)
			{
				unit->setPosition(invisObj.rect.left - unit->getGlobalBounds().width + unit->getHitBoxOffsetX(), unit->getGlobalBounds().top);
				unit->setHitBoxPos(invisObj.rect.left - unit->getHitBox().width, unit->getHitBox().top);
				//std::cout << "Collision from left " << std::endl;
			}
			else
			{
				unit->setPosition(invisObj.rect.left + invisObj.rect.width - unit->getHitBoxOffsetX(), unit->getGlobalBounds().top);
				unit->setHitBoxPos(invisObj.rect.left + invisObj.rect.width, unit->getHitBox().top);
				//std::cout << "Collision from right " << std::endl;
			}
			unit->resetVelocityX();
		}






	}
}
