#pragma once
#include <SFML/Graphics.hpp>

enum class DebugType
{
    OUTLINE,
    FILL,
    CENTER,
    ALL
};

class DebugRenderer
{
public:

    static sf::RectangleShape getOutline(sf::Sprite &sprite);
    static sf::CircleShape getCenter(sf::Sprite &sprite);
    static sf::RectangleShape getFill(sf::Sprite &sprite);
    

    static void render(sf::Sprite &sprite, DebugType render_type, sf::RenderWindow& wind)
    {

        switch (render_type)
        {
        case DebugType::OUTLINE:
        {
            auto outline = getOutline(sprite);
            wind.draw(outline);
            break;
        }
        case DebugType::FILL:
        {
            auto fill = getFill(sprite);
            wind.draw(fill);
            break;
        }
        case DebugType::CENTER:
        {
            auto center = getCenter(sprite);
            wind.draw(center);
            break;
        }
        case DebugType::ALL:
        {
            auto center = getCenter(sprite);
            auto fill = getFill(sprite);
            auto outline = getOutline(sprite);
            wind.draw(outline);
            wind.draw(fill);
            wind.draw(center);
        }
            //IMPORTANT: sprite origin should be set to the sprite center.
    }
    }

};