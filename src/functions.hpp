#pragma once
#include "Components.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

inline AnimationComponent createAnimation(sf::IntRect frame, GAMECONSTANTS::ANIMATION_DIRECTION dir, float speed, bool islooped )
{
    AnimationComponent tmp;
    tmp.speed = speed;
    tmp.islooped = islooped;
    tmp.dir = dir;
    tmp.frame = frame;
    return tmp;
}
