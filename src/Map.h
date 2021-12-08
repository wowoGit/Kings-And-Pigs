#include "Tmx.h"
#include <SFML/Graphics.hpp> 
#include "Components.h"
#include "TextureLoader.h"
#include <iostream>
#include <vector>

/*
    1. Получить набор тайсетов.
        а) Для каждого тайлсета определить размерность и загрузить вектор тайлов(со спрайтами?).
        б) Для каждого тайла в тайлсете определить набор свойств.
    2. Получить набор слоев.
        а) Получить ссылку на тайл в определенном тайлсете и добавить его в вектор тайлов слоя.


*/
class Map
{

typedef struct {
    int height;
    int width;
} parameters;

 struct Tile
{
    sf::IntRect rect;
};

 struct map_layer
{
    std::vector<sf::Sprite> tiles;
};

struct map_tileset{
    map_tileset(const Tmx::Tileset& tileset): tileset_info(tileset){};
    const Tmx::Tileset& tileset_info;
    std::vector<Tile> tiles_vec;
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
    Map::parameters map_params;
    Map::parameters tile_params;
    std::vector<map_layer> map_layers;
    std::vector<Map::map_tileset> tilesets;
    std::unique_ptr<Tmx::Map> map_ptr;
    void ParseMap();
};


