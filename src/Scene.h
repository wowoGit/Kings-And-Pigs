#pragma once

#include <SFML/Graphics.hpp>
#include <Entt/entt.hpp>
class Entity;


class Scene
 {
     public:
     
     Scene(sf::RenderWindow& window) : wind(window)
     {};
     ~Scene() = default;

     virtual bool update(float dt) = 0;
     virtual bool render(float dt) = 0;
     entt::registry& Reg();
     sf::RenderWindow& Wind();
     private: 

     entt::registry entt_reg;
     sf::RenderWindow& wind;

     friend class Entity;
};