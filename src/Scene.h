#pragma once

#include <SFML/Graphics.hpp>
#include <Entt/entt.hpp>
class Entity;



class Scene
 {
     public:
     
     Scene() = default;
     ~Scene();

     virtual bool update(float dt) = 0;
     virtual bool render() = 0;

     Entity createEntity(const std::string& tag);

     private: 

     entt::registry entt_reg;

     friend class Entity;
};