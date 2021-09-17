#pragma once
#include "BoundariesComponent.h"
class InvisibleBoundaries :
	public BoundariesComponent
{
public:
	void handleCollisionWith(Unit* unit) override;
};

