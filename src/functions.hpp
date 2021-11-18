#include "Components.h"
#include <SFML/Graphics.hpp>

AnimationComponent createAnimation(sf::IntRect frame, ANIMATION_DIRECTION dir, float speed, bool islooped )
{
    AnimationComponent tmp;
    tmp.speed = speed;
    tmp.islooped = islooped;
    tmp.dir = dir;
    tmp.frame = frame;
    return tmp;
}
