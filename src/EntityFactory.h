#pragma once
#include "Components.h"
#include "Constants.h"
#include "Entity.h"
#include "Tmx.h"
#include "TextureLoader.h"
#include "functions.hpp"
#include "Map.h"
class EntityFactory
{
public:
    EntityFactory(Scene* scene_ptr) : scene(scene_ptr) {};
    void createMapObjects(std::vector<Tmx::Object> object_vec);
    void createMapTiles(std::vector<GameMap::map_layer> layer_vec);
private:
    Scene* scene;
    std::vector<Entity> entity_vec;
    Entity createItem();



    void createHero(const Tmx::Object& obj);

};