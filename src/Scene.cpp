#include "Scene.h"
#include "Entity.h"
#include "Components.h"
Entity Scene::createEntity(const std::string& tag)
{
    Entity entity = {entt_reg.create(), this};
    auto TagComp = entity.AddComponent<TagComponent>();
    TagComp.Tag = !empty(tag) ? tag : "Default Name" ;
}
 entt::registry& Scene::Reg() 
    {
        return entt_reg;
    }
sf::RenderWindow& Scene::Wind()
{
    return wind;
}