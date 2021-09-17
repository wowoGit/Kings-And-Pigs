#pragma once
#include "SFML/Graphics.hpp"
#include <vector>


struct InitAnimation
{
	sf::Sprite* targetSprite;
	sf::String texturePath;
	sf::String name;
	float x;
	float y;
	float frameWidth;
	float frameHeight;
	int priority;

};

class Animation
{
public:
	Animation(InitAnimation& InitParameters);
	virtual void runAnimation() = 0;
	sf::String getAnimName();
	sf::Sprite* getCurrentFrame();
	bool isFinished();
	int getPriority();
protected:
	sf::Clock clock;
	std::vector<sf::IntRect> frames;
	std::vector <sf::IntRect> frames_flipped;
	int maxFrames;
	sf::Sprite* animSprite;
	sf::Texture animTexture;
	float frameWidth, frameHeight;
	sf::String animName;
	sf::IntRect currentFrame;
	bool flipped;
	bool finished;
	int priority;

};

