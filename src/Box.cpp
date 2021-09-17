#include "Box.h"

Box::Box(const float x, const float y) : Item(x,y)
{
	health = 10;
	initAnimations();
	HitBox = new HitBoxComponent(sprite.getGlobalBounds(), 0, 0);
	Object boxObj;

	boxObj.rect = sf::IntRect(HitBox->getHitBox());
	solidBox = new SolidBoundaries();
	solidBox->initBoundaries(boxObj);
	boxState = SOLID;

}

void Box::initAnimations()
{
	animManager = new AnimationManager();
	animManager->addOnetimeAnimation(&sprite, "Sprites/box/Idle.png", 0, 0, 22,16, "IDLE", 10);
	animManager->addOnetimeAnimation(&sprite, "Sprites/box/Hit.png", 0, 0, 22,16, "HIT", 10);
	
	
}

void Box::interact(Unit* player)
{
	if (boxState == SOLID)
	{
		solidBox->handleCollisionWith(player);
	}
}

void Box::update()
{
	switch (boxState)
	{
	case SOLID:
		animManager->setCurrentAnimation("IDLE");
		animManager->runCurrentAnimation();
		break;
	case HIT:
		animManager->setCurrentAnimation("HIT");
		animManager->runCurrentAnimation();
		boxState = SOLID;
		break;
	case SHATTERED:
		sprite.setColor(sf::Color::Transparent);
		
		for (BoxPiece* piece : shatteredBox)
		{
			piece->update();
		}
		break;
	}
}

void Box::getHitWith(int _dmg)
{
	if (this->isAlive()) // is Solid, � ���� ������
	{
		health -= _dmg;
		boxState = HIT;
		
	}
	else 
	{
		boxState = SHATTERED;
		for (size_t i = 0; i < 4; i++)
		{
			shatteredBox.push_back(new BoxPiece(this->getPosition().x, this->getPosition().y, "BOXPIECE" + std::to_string(i)));
		}
	}
}

void Box::render(sf::RenderTarget& render)
{

	if (boxState == SHATTERED)
	{
		for (BoxPiece* piece : shatteredBox)
		{
			piece->render(render);
		}
	}
	else
	{
		Entity::render(render);
	}
}
