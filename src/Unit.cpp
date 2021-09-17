#include "Unit.h"

void Unit::resetVelocityY()
{
	velocity.y = 0.f;
}

void Unit::resetVelocityX()
{
	velocity.x = 0.f;
}

void Unit::resetOnGround()
{
	onGround = true;
}

sf::CircleShape Unit::getAttackArea()
{
	return attackArea;
}
