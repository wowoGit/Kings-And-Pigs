#pragma once
#include "SFML/Graphics.hpp"
class HitBoxComponent
{
public:
	HitBoxComponent(sf::FloatRect _src, float _offsetX = 0, float _offsetY = 0);
	sf::FloatRect& getHitBox();
	float getOffsetX() const;
	float getOffsetY() const;
	sf::Vector2f getHitBoxCenter();
	void moveHitBox(sf::Vector2f velocity);
	void setHitBoxPos(float _x, float _y);
private:
	sf::FloatRect hitBox;
	float offsetX, offsetY;


};

