#pragma once
#include <iostream>
#include <vector>
#include "level.h"
#include "Unit.h"
class BoundariesComponent
{
public:
	void initBoundaries(std::vector<Object> _boundaries);
	void initBoundaries(Object _boundaries);
	std::vector<Object> getBoundaries();
	virtual void handleCollisionWith(Unit* unit) = 0;
private:
	std::vector<Object> boundaries;
};

