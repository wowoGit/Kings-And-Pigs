#include "Player.h"
#include <iostream>
Player::Player(float _x, float _y) : Unit(_x,_y)
{
	animManager = new AnimationManager();
	initAnimations();
	HitBox = new HitBoxComponent(sprite.getGlobalBounds(), 30, 16);
	this->velocityMax = 5.f;
	this->velocityMin = 1.f;
	this->acceleration = 1.2f;
	this->resistance = 0.85f;
	this->gravity = 1.5f;
	this->velocityMaxY = 30.f;
	onGround = false;

	health = 10;
	dmg = 3;
	Attacking = false;
	attackLock = false;
	attackRange = 25.f;
	attackArea.setRadius(10);
	attackArea.setOrigin({ 10,  10 });
#ifdef DEBUG
	attackArea.setFillColor(sf::Color::White);
#endif // DEBUG

	
}
void Player::initAnimations()
{

	animManager->addLoopedAnimation(&sprite, "Sprites/king/Run.png", 0, 0, 78, 58, "RUN_RIGHT", 10);
	animManager->addLoopedAnimation(&sprite, "Sprites/king/idle.png", 0, 0, 78, 58, "IDLE", 10);
	animManager->addLoopedAnimation(&sprite, "Sprites/king/Run.png", 0, 0, 78, 58, "RUN_LEFT", 10);
	animManager->addLoopedAnimation(&sprite, "Sprites/king/Jump.png", 0, 0, 78, 58, "JUMP", 10);
	animManager->addLoopedAnimation(&sprite, "Sprites/king/Fall.png", 0, 0, 78, 58, "FALL", 10);
	animManager->addLoopedAnimation(&sprite, "Sprites/king/Ground.png", 0, 0, 78, 58, "DUCK", 10);
	animManager->addLoopedAnimation(&sprite, "Sprites/king/Attack_main.png",0, 0, 78, 58, "ATTACK", 5);
	animManager->addLoopedAnimation(&sprite, "Sprites/king/Hit.png",0, 0, 78, 58, "HIT", 5);
	animManager->addLoopedAnimation(&sprite, "Sprites/king/Door_In.png",0, 0, 78, 58, "ENTRY_LEVEL", 5);
	animManager->addOnetimeAnimation(&sprite, "Sprites/king/Dead.png",0, 0, 78, 58, "DEAD", 0);
	animManager->setCurrentAnimation("ENTRY_LEVEL");
}
bool Player::isAttacking()
{
	return Attacking;
}

void Player::resetAttackLock()
{
	attackLock = false;
}
void Player::move(const float _x, const float _y)
{
	this->velocity.x += _x * acceleration;

	if (abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0) ? -1.f : 1.f);
	}

	this->velocity.y += _y * 1.f;

}
void Player::getHitWith(int dmg)
{
	if (this->isAlive())
	{
		health -= dmg;
		gotHit = true;
		resetVelocityX();
		move(0.f, 5.f);
		attackLock = true;
	}
	
}
void Player::updatePhysics()
{
	this->velocity.y += 1.f * this->gravity;
	
	if (abs(this->velocity.y) > this->velocityMaxY)
	{
		this->velocity.y = this->velocityMaxY * ((this->velocity.y > 0) ?  1.f: -1.f);

	}
	this->velocity *= resistance;

	if (abs(this->velocity.x) < velocityMin)
	{
		this->velocity.x = 0;

	}
	if (abs(velocity.y) < velocityMin)
	{
		this->velocity.y = 0;
	}
	this->sprite.move(velocity);
	this->HitBox->moveHitBox(velocity);
	attackArea.setPosition(HitBox->getHitBoxCenter().x + (attackRange* directionX), HitBox->getHitBoxCenter().y+10);
}

void Player::updateMovement()
{
	Attacking = false;
	if (!this->isAlive())
	{
		animManager->setCurrentAnimation("DEAD");
		resetVelocityX();
		return;
	}
	if (onGround)
	{
		animManager->setCurrentAnimation("IDLE");
		//playerState = IDLE;
	}
	else if (velocity.y > 0)
	{
		animManager->setCurrentAnimation("FALL");
		//playerState = FALL;
		//std::cout << "falling\n";
		
	}
	if (gotHit)
	{
		animManager->setCurrentAnimation("HIT");
		resetVelocityX();
		gotHit = false;
		//std::cout << "hit\n";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && (playerState != JUMP && playerState != FALL))
	{

		animManager->setCurrentAnimation("DUCK");
		//playerState = DUCK;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && playerState != DEAD)
	{
		this->move(1.f, 0);
		if (onGround)
		{
			animManager->setCurrentAnimation("RUN_RIGHT");
		}

		sprite.setScale(1.f, 1.f);
		sprite.setOrigin(0, 0);
		directionX = 1;
		//playerState = RUN_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		this->move(-1.f, 0);
		if (onGround)
		{
			animManager->setCurrentAnimation("RUN_LEFT");
		}
		sprite.setScale(-1.f, 1.f);
		sprite.setOrigin(getGlobalBounds().width / 1.f, 0);
		directionX = -1;
		//playerState = RUN_LEFT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && 
		onGround && jumpCooldownTimer.getElapsedTime().asSeconds() > jumpCooldown)
	{
		if (onGround)
		{
			this->move(0, -55.f);
			onGround = false;
		}
		animManager->setCurrentAnimation("JUMP");
		//playerState = JUMP;
		jumpCooldownTimer.restart();
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !attackLock)
	{
		animManager->setCurrentAnimation("ATTACK");
		Attacking = true;
		attackLock = true;
	}
	
	//std::cout << playerState << std::endl;
}


void Player::attack(Unit* target)
{
	if (this->isAttacking())
	{
		target->getHitWith(this->dmg);
	}
}

void Player::attack(Item* target)
{
	if (this->isAttacking())
	{
		target->getHitWith(this->dmg);
	}
}





void Player::update()
{
	animManager->runCurrentAnimation();
	updateMovement();
	updatePhysics();
}

