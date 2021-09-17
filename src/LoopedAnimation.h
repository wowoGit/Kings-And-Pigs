#include "Animation.h"
#pragma once

class LoopedAnimation : public Animation
{
public:
	LoopedAnimation(InitAnimation& InitParameters) : Animation(InitParameters)
	{};
	void runAnimation() override;
};

