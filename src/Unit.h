#pragma once
#include "Entity.h"
class Unit : public Entity
{
public:
	Unit(const float x, const float y) : Entity(x, y) {};
	void resetVelocityY();
	void resetVelocityX();
	void resetOnGround();
	virtual void attack(Unit* target) = 0;
	virtual void resetAttackLock() = 0;
	sf::CircleShape getAttackArea();
	virtual void move(const float _x, const float _y) = 0;

protected:
	sf::Vector2f velocity;
	bool Attacking = false;
	bool attackLock = false; // очень грязный способ. Поменять.
	int dmg = 0;
	float attackRange = 0;
	sf::CircleShape attackArea;
	bool onGround = true;
};

