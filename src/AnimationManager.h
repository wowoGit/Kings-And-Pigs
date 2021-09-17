#pragma once
//#include "Animation.h"
#include "LoopedAnimation.h"
#include "OnetimeAnimation.h"
class AnimationManager
{

public:
	void addLoopedAnimation(sf::Sprite* targetSprite, sf::String texturePath, float x, float y, float frameWidth, float frameHeight, sf::String name, int priority);
	void addOnetimeAnimation(sf::Sprite* targetSprite, sf::String texturePath, float x, float y, float frameWidth, float frameHeight, sf::String name, int priority);
	void setCurrentAnimation(sf::String name);
	sf::Sprite* getCurrentFrame();
	void runCurrentAnimation();
	bool currentAnimationIsOver();
	~AnimationManager();
private:
	Animation* currentAnimation = nullptr;
	std::vector<Animation*> animVect;

};

