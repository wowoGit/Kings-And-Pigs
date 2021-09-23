#pragma once

#include <string>
#include <SFML/Graphics.hpp>
//ENTITY COMPONENTS 

struct TagComponent
{
    std::string Tag;
    TagComponent() = default;
    TagComponent(TagComponent& other) = default;
    TagComponent(const std::string& tag): Tag(tag)
    {}
};

struct SpriteComponent
{
    sf::Sprite Sprite;
    SpriteComponent(sf::Texture& texture)
    {
        Sprite.setTexture(texture);
    }
    SpriteComponent() = default;
    SpriteComponent(SpriteComponent& other) = default; 
};

struct MoveComponent
{
    float x;
    float y;
    MoveComponent(float x1 = 0, float y1 = 0) : x(x1), y(y1)
    {}
    MoveComponent() = default;
    MoveComponent(MoveComponent& other) = default;
    sf::Time z = sf::Clock::getElapsedTime();
}