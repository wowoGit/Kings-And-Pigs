#include "Scene.h"
#include "Entity.h"
#include "Components.h"
 entt::registry& Scene::Reg() 
    {
        return entt_reg;
    }
sf::RenderWindow& Scene::Wind()
{
    return wind;
}