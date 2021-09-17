#pragma once
#include "Animation.h"
class OnetimeAnimation :
	public Animation
{
public:
	OnetimeAnimation(InitAnimation& InitParameters) : Animation(InitParameters)
	{};
	void runAnimation() override;
};

