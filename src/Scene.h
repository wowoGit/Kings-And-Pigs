#pragma once

#include <SFML/Graphics.hpp>
#include <Entt/entt.hpp>
class Entity;


class Scene
 {
     public:
     
     Scene(sf::RenderWindow& window) : wind(window)
     {};
     ~Scene();

     virtual bool update(float dt) = 0;
     virtual bool render() = 0;
     entt::registry& Reg();
     Entity createEntity(const std::string& tag);
     sf::RenderWindow& Wind();
     private: 

     entt::registry entt_reg;
     sf::RenderWindow& wind;

     friend class Entity;
};