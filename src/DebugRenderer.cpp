#include "DebugRenderer.h"



sf::RectangleShape DebugRenderer::getOutline(sf::Sprite& sprite)
{
    sf::RectangleShape shape;
    shape.setSize({sprite.getTextureRect().width, sprite.getTextureRect().height});
    shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
    shape.setOutlineColor(sf::Color::Green);
    shape.setOutlineThickness(1.f);
    shape.setFillColor(sf::Color::Transparent);
    shape.setPosition(sprite.getPosition());
    return shape;
}

sf::RectangleShape DebugRenderer::getFill(sf::Sprite& sprite)
{

    sf::RectangleShape shape;
    shape.setSize({sprite.getTextureRect().width, sprite.getTextureRect().height});
    shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
    shape.setFillColor(sf::Color::Magenta);
    shape.setPosition(sprite.getPosition());
    return shape;
}
sf::CircleShape DebugRenderer::getCenter(sf::Sprite& sprite)
{

        sf::CircleShape center;
        center.setFillColor(sf::Color::Red);
        center.setRadius(5.f);
        center.setOrigin(center.getRadius() / 2, center.getRadius() / 2);
        center.setPosition(sprite.getPosition());
        return center;
}





