#pragma once
#include "BoundariesComponent.h"
#include "math.h"
class StickBoundaries :
	public BoundariesComponent
{
public:
	void handleCollisionWith(Unit* unit) override;
};

