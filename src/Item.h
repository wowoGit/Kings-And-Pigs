#pragma once 
#include "Entity.h"
#include "Unit.h"

class Item : public Entity
{
public:
	Item(const float x, const float y);
	virtual void interact(Unit* player) = 0;
	virtual void render(sf::RenderTarget& render) = 0;
};