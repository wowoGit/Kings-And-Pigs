#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <vector>


Entity::Entity(const float _x, const float _y)
{
	sprite.setPosition(_x, _y);
	
}

sf::Vector2f Entity::getPosition() const
{
	return this->sprite.getPosition();
}

sf::FloatRect Entity::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

sf::FloatRect Entity::getHitBox() const
{
	return HitBox->getHitBox();
}

float Entity::getHitBoxOffsetX() const
{
	return HitBox->getOffsetX();
}

float Entity::getHitBoxOffsetY() const
{
	return HitBox->getOffsetY();
}



bool Entity::isAlive()
{
	return health > 0;
}

void Entity::setPosition(const float x, const float y)
{

	this->sprite.setPosition(x, y);

}

void Entity::setHitBoxPos(const float x, const float y)
{
	HitBox->setHitBoxPos(x, y);
}

void Entity::render(sf::RenderTarget& target)
{

	target.draw(this->sprite);
}

bool Entity::currentAnimationIsOver()
{
	return animManager->currentAnimationIsOver();
}

Entity::~Entity()
{
	delete animManager;
	delete HitBox;
}
