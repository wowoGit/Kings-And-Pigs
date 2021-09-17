#pragma once
#include "SFML/Graphics.hpp"
#include "HitBoxComponent.h"
#include <vector>
#include "AnimationManager.h"
class Entity
{
public:
	Entity(const float _x, const float _y);
	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;
	sf::FloatRect getHitBox() const;
	float getHitBoxOffsetX() const;
	float getHitBoxOffsetY() const;
	virtual void getHitWith(int _dmg) = 0;
	bool isAlive();
	void setPosition(const float x, const float y);
	void setHitBoxPos(const float x, const float y);
	void render(sf::RenderTarget& render);
	virtual void update() = 0;
	virtual void initAnimations() = 0;
	bool currentAnimationIsOver();
	~Entity();
	
protected:
	sf::Sprite sprite;
	AnimationManager* animManager;
	HitBoxComponent* HitBox;
	int health;

	
};

