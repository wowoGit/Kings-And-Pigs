#include "HitBoxComponent.h"
#include <iostream>
HitBoxComponent::HitBoxComponent(sf::FloatRect _src, float _offsetX, float _offsetY)
{
	offsetX = _offsetX, offsetY = _offsetY;
	hitBox.left = _src.left + offsetX;
	hitBox.width = _src.width - offsetX*2;
	hitBox.top = _src.top + offsetY;
	hitBox.height = _src.height - offsetY*2;
	//setHitBoxPos(hitBox.left, hitBox.top + offsetY);
	
	
}

sf::FloatRect& HitBoxComponent::getHitBox()
{
	return hitBox;
}

float HitBoxComponent::getOffsetX() const
{
	return offsetX;
}

float HitBoxComponent::getOffsetY() const
{
	return offsetY;
}

sf::Vector2f HitBoxComponent::getHitBoxCenter()
{
	return sf::Vector2f(hitBox.left +(hitBox.width/2) , hitBox.top +( hitBox.height / 2));
}

void HitBoxComponent::moveHitBox(const sf::Vector2f velocity)
{
	hitBox.left += velocity.x;
	hitBox.top += velocity.y;
}

void HitBoxComponent::setHitBoxPos(float _x, float _y)
{
	hitBox.left = _x;
	hitBox.top = _y;
}

