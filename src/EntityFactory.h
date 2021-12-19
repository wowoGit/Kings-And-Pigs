#pragma once
#include "Components.h"
#include "Entity.h"
#include "Tmx.h"
#include "TextureLoader.h"
#include "functions.hpp"

class EntityFactory
{
public:
    EntityFactory(Scene* scene_ptr) : scene(scene_ptr) {};
    void createMapObject(const Tmx::Object);
private:
    Scene* scene;
    Entity createMainCharacter(const Tmx::Object &);
    Entity createMapTile(const Tmx::Tile &);
    Entity createItem();
};