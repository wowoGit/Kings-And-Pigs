#pragma once
#include <SFML/Graphics.hpp>
#include "AnimationManager.h"
#include "HitBoxComponent.h"
#include "Unit.h"
#include "Item.h"


class Player : public Unit
{
public:
	Player(float _x = 0, float _y = 0);
	void attack(Unit* target) override;
	void attack(Item* target);
	void resetAttackLock();
	void update() override;
	void getHitWith(int _dmg);
private:
	enum STATE { IDLE, RUN_LEFT, RUN_RIGHT, JUMP, DUCK, ATTACK, FALL, DEAD };
	void updatePhysics();
	void updateMovement();
	void initAnimations() override;
	void move(const float _x, const float _y);
	bool isAttacking();
	//movement vars
	STATE playerState;
	bool gotHit = false;
	float jumpCooldown = 1.f;
	sf::Clock jumpCooldownTimer;
	//sf::Vector2f velocity;
	int directionX = 1;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float resistance;
	float gravity;
	float velocityMaxY;


	//attacking vars
	
	
};

