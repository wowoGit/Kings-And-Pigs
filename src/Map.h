#include "Tmx.h"
#include <SFML/Graphics.hpp> 
#include "Components.h"
#include "TextureLoader.h"
#include "EntityFactory.h"
#include <iostream>
#include <vector>

class Map
{

    struct map_layer
    {
        std::vector<sf::Sprite> tiles;
    };

    struct map_tileset{
        map_tileset(const Tmx::Tileset& tileset): tileset_info(tileset){};
        const Tmx::Tileset& tileset_info;
        std::vector<sf::IntRect> tiles_vec;
        sf::Image image;
        void fillTileRects();
    };

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

    void render(sf::RenderWindow& wind);

    private:
    const Map::map_tileset& findTilesetbyGID(int gid);
    std::vector<map_layer> map_layers;
    std::vector<Map::map_tileset> tilesets;
    std::unique_ptr<Tmx::Map> map_ptr;
    void ParseMap();
};

