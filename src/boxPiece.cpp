#include "boxPiece.h"

BoxPiece::BoxPiece(const float x, const float y, std::string boxPiece) : Item(x,y)
{
	pieceNumber = boxPiece;
	initAnimations();
	acceleration = 1.2f;
	gravity = 1.2f;
	resistance = 0.85f;
	initYpos = y;
	move(rand()% 10, -20);
}

void BoxPiece::initAnimations()
{
	animManager = new AnimationManager();
	animManager->addOnetimeAnimation(&sprite, "Sprites/box/" + pieceNumber + ".png", 0, 0, 10, 10, pieceNumber, 10);
	animManager->setCurrentAnimation(pieceNumber);
}

void BoxPiece::interact(Unit* player)
{
	return;
}

void BoxPiece::update()
{
	updatePhysics();
	animManager->runCurrentAnimation();
}

void BoxPiece::updatePhysics()
{
	velocity.y += 1.f * gravity;
	velocity *= resistance;
	sprite.move(velocity);
	if (getPosition().y >= initYpos)
	{
		velocity.x = 0;
		velocity.y = 0;
		setPosition(getPosition().x, initYpos);
	}
	
}

void BoxPiece::move(const float x, const float y)
{
	velocity.x += x * acceleration;
	velocity.y = 1.f * y;
}

void BoxPiece::getHitWith(int _dmg)
{
	return;
}

void BoxPiece::render(sf::RenderTarget& render)
{
	Entity::render(render);
}
