#pragma once
#include "BoundariesComponent.h"
class SolidBoundaries :
	public BoundariesComponent
{
public:
	void handleCollisionWith(Unit* unit) override;
};

