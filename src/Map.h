#pragma once
#include "Tmx.h"
#include <SFML/Graphics.hpp> 
#include "Components.h"
#include "TextureLoader.h"
#include <iostream>
#include <vector>


namespace GameMap
{


enum class TileType { SOLID, WATER, QUICKSAND, DECORATION, UNDEFINED}; 

struct layer_tile
{
    TileType type;
    const sf::Texture& texture_ref;
    const sf::IntRect rect;
    const sf::Vector2f sprite_pos;
};



struct map_layer
{
    std::vector<layer_tile> tiles;
};



struct map_tileset{
    map_tileset(const Tmx::Tileset& tileset): tileset_info(tileset){};
    const Tmx::Tileset& tileset_info;
    std::vector<sf::IntRect> tiles_vec;
    sf::Image image;
    void fillTileRects();
};

// There will be different tile types each of those types will describe a specific set a components to be binded to.
// For now i will be using only the solid type (The lack of free-to-use tilesets is DEFINITELY not the reason).

class Map
{


    public:
    Map(std::string filepath)
    {
        try
        {
        map_ptr = std::make_unique<Tmx::Map>();
        map_ptr->ParseFile(filepath);
        ParseMap();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        
    }
    std::vector<Tmx::Object> getObjects();
    std::vector<map_layer> getMapLayers();

    private:
    const map_tileset& findTilesetbyGID(int gid);
    std::vector<map_layer> map_layers;
    std::vector<Tmx::Object> map_objects;
    std::vector<map_tileset> tilesets;
    std::unique_ptr<Tmx::Map> map_ptr;
    std::unordered_map<std::string, TileType> tileTypeMap {{"solid" , TileType::SOLID}};
    //Load a tmx map.
    void ParseMap();



};

}