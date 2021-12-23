#pragma once
#include <string>
#include "Constants.h"
//#include "InputCommands.hpp"
#include <SFML/Graphics.hpp>
//ENTITY COMPONENTS 

struct TagComponent
{
    std::string Tag;
};

struct SpriteComponent
{
    sf::Sprite Sprite;
};

struct RenderableComponent
{
    GAMECONSTANTS::RENDER_PRIORITY prio;
};

struct AnimationComponent
{
    float speed;
    GAMECONSTANTS::ANIMATION_DIRECTION dir;
    sf::IntRect frame;
    bool islooped;

};

struct AnimationPool
{
    std::map<std::string, AnimationComponent> pool;
    std::string current;
};

struct MoveComponent
{
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f current_speed; 
    sf::Vector2f max_speed; 
};

struct PhysicsComponent
{
    float resistance;
    float gravity;
};


struct HitBoxComponent
{
    sf::FloatRect hitbox;
};


struct CollidableComponent
{
    sf::IntRect body;
};

struct StateComponent
{
    std::string state;
};


// Tag components for FSM in the future

struct PlayerTag
{}; //for some reason component with no fields doesnt work (WTFF)