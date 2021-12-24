#include "Map.h"

void GameMap::map_tileset::fillTileRects()
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



void GameMap::Map::ParseMap()
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
        const auto& tileLayer = map_ptr->GetTileLayer(i);
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
                const auto& map_tile = tileLayer->GetTile(tile_id);
                const auto& tileset_tile = tileset.tileset_info.GetTile(map_tile.id);
                GAMECONSTANTS::TileType type = GAMECONSTANTS::TileType::UNDEFINED;
                if(tileset_tile){
                const auto& tile_type = tileset_tile->GetType();
                if ( tile_type != "")
                {
                    auto it = tileTypeMap.find(tile_type);
                    
                    if (it != tileTypeMap.end())
                    {
                        type = it->second;
                    }
                }
                else 
                {
                    std::cerr << "Tile with gid = " << map_tile.gid << " did not have a type. Was that intended?\n";
                }
                }

                //load tile sprite and corresponding rect
                const sf::IntRect rect = tileset.tiles_vec.at(tile_id);

                const auto texture_name = tileset.tileset_info.GetName();
                const auto& tileset_texture = TextureLoader::loadFromImage(tileset.image, texture_name);

                sf::Vector2f sprite_pos(x* rect.width, y * rect.height);

                layer_tile tile{type, tileset_texture, rect, sprite_pos};
                layer.tiles.push_back(tile);
            }
        }
        map_layers.push_back(std::move(layer));
    }


    for (int i = 0; i < map_ptr->GetNumObjectGroups(); i++)
    {
        const auto& object_group = map_ptr->GetObjectGroup(i);

        for(size_t object_idx = 0; object_idx < object_group->GetNumObjects(); ++object_idx)
        {            
            const auto& object = object_group->GetObject(object_idx);
            map_objects.push_back(*object);
        }
        
    }
    
    
    
}

const GameMap::map_tileset& GameMap::Map::findTilesetbyGID(int gid)
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
std::vector<Tmx::Object> GameMap::Map::getObjects() 
{
    return map_objects;
}

std::vector<GameMap::map_layer> GameMap::Map::getMapLayers() 
{
    return map_layers;
}
