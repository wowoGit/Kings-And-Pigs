#include "Map.h"

void Map::map_tileset::fillTileRects()
{

    const auto total_tiles = tileset_info.GetTileCount();
    const auto tile_width = tileset_info.GetTileWidth();
    const auto tile_height = tileset_info.GetTileHeight();

    const auto columns = tileset_info.GetColumns();
    const auto rows = total_tiles / columns;
    for(int x = 0; x < rows; x++)
    {
        for (int y = 0; y < columns; y++)
        {
            sf::IntRect rect(y * tile_width, x * tile_height,tile_width,tile_height);
            tiles_vec.push_back(rect);
            //IMPLEMENT: binding components depending on a tile type(factory method?).
        }
        
    }
}

void Map::render(sf::RenderWindow& wind)
{
    int counter_row = 0;
    int countercol=0;
    for(const auto& layer : map_layers)   
    {
        for(const auto& tile : layer.tiles)
        {
            wind.draw(tile);
        }
    }
}



void Map::ParseMap()
{

    for (int i = 0; i < map_ptr->GetNumTilesets(); i++)
    {
        //setup map tileset and populate the rects
        // to create a sprite in the future.
        const Tmx::Tileset *ts = map_ptr->GetTileset(i);
        map_tileset map_ts(*ts);

        //texture name and texture path will be identical.
        const auto texture_path = "maps/" + ts->GetImage()->GetSource();
        const auto texture_name = ts->GetName();
        map_ts.fillTileRects();
        map_ts.image.loadFromFile(texture_path);
        tilesets.push_back(std::move(map_ts));
    } 

    for (int i = 0; i < map_ptr->GetNumTileLayers(); i++)
    {
        const auto tileLayer = map_ptr->GetTileLayer(i);
        map_layer layer;
        for (int y = 0; y < tileLayer->GetHeight(); ++y)
        {
            for (int x = 0; x < tileLayer->GetWidth(); ++x)
            {
                //get tileset id for a specific tile in a layer
               int tileset_id = tileLayer->GetTileTilesetIndex(x,y);
               if(tileset_id == -1)
               {
                   continue;
               }
               const auto& tileset = tilesets.at(tileset_id);
               int tile_id = tileLayer->GetTileId(x,y);
               const sf::IntRect rect = tileset.tiles_vec.at(tile_id);

               //load tile sprite and corresponding rect
               sf::IntRect tile_rect = rect;
               sf::Sprite tile_sprite;

               //get tileset texture and populate layers' tile collection
               const auto texture_name = tileset.tileset_info.GetName();
               const auto& tileset_texture = TextureLoader::loadFromImage(tileset.image, texture_name);
               tile_sprite.setTexture(tileset_texture);
               tile_sprite.setTextureRect(tile_rect);
               tile_sprite.setPosition(rect.getPosition().x,rect.getPosition().y);
               layer.tiles.push_back(tile_sprite);
            }
        }
        map_layers.push_back(std::move(layer));
    }


    for (int i = 0; i < map_ptr->GetNumObjectGroups(); i++)
    {
        const auto& object_group = map_ptr->GetObjectGroup(i);

        for(size_t object_idx = 0; i < object_group->GetNumObjects(); ++object_idx)
        {
            
        }
        
    }
    
    
    
}

const Map::map_tileset &Map::findTilesetbyGID(int gid)
{
    if (tilesets.empty())
    {
        std::cout << "Tileset collection is empty!\n";
    }
    try
    {
        map_tileset* tileset_to_use = &tilesets.front();
        for (int i = 0; i < tilesets.size(); i++)
        {
            auto first_gid = tilesets[i].tileset_info.GetFirstGid();
            if (gid < first_gid)
            {
                break;
            }
            tileset_to_use = &tilesets[i];
        }
        return *tileset_to_use;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what();
    }
        
}