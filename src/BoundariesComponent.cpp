#include "BoundariesComponent.h"

void BoundariesComponent::initBoundaries(std::vector<Object> _boundaries)
{
	this->boundaries = _boundaries;
}

void BoundariesComponent::initBoundaries(Object _boundaries)
{
	boundaries.push_back(_boundaries);
}

std::vector<Object> BoundariesComponent::getBoundaries()
{
	return boundaries;
}
