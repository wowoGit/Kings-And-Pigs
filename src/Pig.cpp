#include "Pig.h"
#include <random>
#include <iostream>
Pig::Pig(const int _x, const int _y) : Unit(_x,_y)
{
	animManager = new AnimationManager();
	initAnimations();
	HitBox = new HitBoxComponent(sprite.getGlobalBounds(), 14, 12);
	velocity.x = VelocityXMax;
	velocity.y = VelocityYMax;
	health = 10;
	dmg = 3;
	moveDirection = 1;

	attackRange = 10.f;
	attackArea.setRadius(5);
	attackArea.setOrigin({ 5,  5 });
	//attackArea.setFillColor(sf::Color::Transparent);
}

void Pig::initAnimations()
{
	animManager->addLoopedAnimation(&sprite, "Sprites/Pig/Run.png", 0, 0, 34,28,"RUN_RIGHT", 10);
	animManager->addLoopedAnimation(&sprite, "Sprites/Pig/Idle.png", 0, 0,34,28, "IDLE", 10);
	animManager->addLoopedAnimation(&sprite, "Sprites/Pig/Run.png", 0, 0, 34,28,"RUN_LEFT", 10);
	animManager->addLoopedAnimation(&sprite, "Sprites/Pig/Hit.png", 0, 0, 34,28,"HIT", 5);
	animManager->addLoopedAnimation(&sprite, "Sprites/Pig/Attack.png", 0, 0, 34,28,"ATTACK", 5);
	animManager->addOnetimeAnimation(&sprite, "Sprites/Pig/Dead.png", 0, 0, 34,28,"DEAD", 0);
	animManager->setCurrentAnimation("IDLE");
}

void Pig::update()
{
	setAnimationOnState();
	animManager->runCurrentAnimation();
	generateDirection();
	move(moveSpeed * moveDirection, 0);
	calculateState();
	resetAttackLock();
	
	
	
}

void Pig::getHitWith(int _dmg)
{
	if (this->isAlive())
	{
		health -= _dmg;
		pigState = HIT;
		velocity.x = 0;
		std::cout << "hit\n";
	}
	if (!this->isAlive())
	{
		pigState = DEAD;
	}
}

void Pig::move(const float x, const float y)
{
	if (this->isAlive())
	{
		velocity.x = x;
		velocity.y = y;
		sprite.move(velocity);
		this->HitBox->moveHitBox(velocity);
		int dir = 1 ? velocity.x > 0 : -1;
		attackArea.setPosition(HitBox->getHitBoxCenter().x + (attackRange * dir), HitBox->getHitBoxCenter().y);
		
		//std::cout << velocity.x << std::endl;
	}
	
}

void Pig::generateDirection()
{
	if (DirGenerationTimer.getElapsedTime().asSeconds() >= movementCooldown)
	{
		moveDirection = rand() % 3 - 1;
		attackArea.setPosition(attackRange * moveDirection, HitBox->getHitBoxCenter().y);
		DirGenerationTimer.restart();
		//std::cout << moveDirection << std::endl;
	}
}


void Pig::setAnimationOnState()
{
	if (pigState == RUN_RIGHT)
	{

		animManager->setCurrentAnimation("RUN_RIGHT");
		sprite.setScale(-1.f, 1.f);
		sprite.setOrigin(sprite.getGlobalBounds().width / 1.f, 0);

	}
	else if (pigState == RUN_LEFT)
	{
		animManager->setCurrentAnimation("RUN_LEFT");
		sprite.setScale(1.f, 1.f);
		sprite.setOrigin(0, 0);
	}
	else 
	{
		animManager->setCurrentAnimation("IDLE");
	}
	if (pigState == HIT)
	{
		
		animManager->setCurrentAnimation("HIT");
		resetVelocityX();
	}
	if (pigState == DEAD)
	{
		animManager->setCurrentAnimation("DEAD");
		resetVelocityX();
	}
	if (pigState == ATTACK)
	{
		animManager->setCurrentAnimation("ATTACK");
		//resetVelocityX();
		std::cout << "not moving" << std::endl;
	}
	//std::cout << pigState << std::endl;
	
	

}

void Pig::calculateState()
{
	if (this->isAlive())
	{
		if (velocity.x > 0)
		{
			pigState = RUN_RIGHT;
		}
		else if (velocity.x < 0)
		{
			pigState = RUN_LEFT;
		}
		else
		{
			pigState = IDLE;
		}
	}
	
}

void Pig::resetAttackLock()
{
	if (attackCooldownTimer.getElapsedTime().asSeconds() > attackCoolDown)
	{
		attackCooldownTimer.restart();
		attackLock = false;
	}
	else
	{
		resetVelocityX();
	}
}

void Pig::attack(Unit* target)
{
	if (!attackLock)
	{
		target->getHitWith(dmg);
		attackLock = true;
		std::cout << "asd\n";
		pigState = ATTACK;
	}
}
