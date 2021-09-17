#include "level.h"
#include <iostream>
#include "tinyxml2.h"
using namespace tinyxml2;
int Object::GetPropertyInt(std::string name)
{
    return atoi(properties[name].c_str());
}

float Object::GetPropertyFloat(std::string name)
{
    return strtod(properties[name].c_str(), NULL);
}

std::string Object::GetPropertyString(std::string name)
{
    return properties[name];
}

bool Level::LoadFromFile(std::string filename)
{
    XMLDocument levelFile;

	// ��������� XML-�����
    levelFile.LoadFile(filename.c_str());
    if(levelFile.LoadFile(filename.c_str()))
    {
        std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
        return false;
    }

	// �������� � ����������� map
    XMLElement *map;
    map = levelFile.FirstChildElement("map");

	// ������ �����: <map version="1.0" orientation="orthogonal"
	// width="10" height="10" tilewidth="34" tileheight="34">
    width = atoi(map->Attribute("width"));
    height = atoi(map->Attribute("height"));
    tileWidth = atoi(map->Attribute("tilewidth"));
    tileHeight = atoi(map->Attribute("tileheight"));

	// ����� �������� �������� � ������������� ������� �����
    std::vector<tileSet*> tilesets;
    XMLElement* tilesetElement;
    for(tilesetElement = map->FirstChildElement("tileset");tilesetElement!= NULL; tilesetElement = tilesetElement->NextSiblingElement("tileset"))
    {
        tileSet *newTileSet = new tileSet();
        newTileSet->tileHeight = 32;
        newTileSet->tileWidth = 32;
        newTileSet->firstGID = atoi(tilesetElement->Attribute("firstgid"));
        XMLElement* image;
        image = tilesetElement->FirstChildElement("image");
        newTileSet->setImage(image->Attribute("source"));
        //newTileSet.setTexture(newTileSet.image);

        tilesets.push_back(newTileSet);
    }
    


	// ������ �� ������
    XMLElement *layerElement;
    layerElement = map->FirstChildElement("layer");
    while(layerElement)
    {
        Layer layer;
		
		// ���� ������������ opacity, �� ������ ������������ ����, ����� �� ��������� �����������
        if (layerElement->Attribute("opacity") != NULL)
        {
            float opacity = strtod(layerElement->Attribute("opacity"), NULL);
            layer.opacity = 255 * opacity;
        }
        else
        {
            layer.opacity = 255;
        }

		// ��������� <data>
        XMLElement *layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if(layerDataElement == NULL)
        {
            std::cout << "Bad map. No layer information found." << std::endl;
        }

		// ��������� <tile> - �������� ������ ������� ����
        XMLElement *tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if(tileElement == NULL)
        {
            std::cout << "Bad map. No tile information found." << std::endl;
            return false;
        }

        int x = 0;
        int y = 0;
        std::cout << "before";
        tileSet *tileSetToUse = tilesets.front();
        std::cout << "after";
        while(tileElement)
        {
            int tileGID = atoi(tileElement->Attribute("gid"));
            
            for (tileSet* tl : tilesets)
            {
                if (tileGID < tl->getFirstGID())
                {
                    break;
                }
                tileSetToUse = tl;
            }
            int i = 0;
            int subRectToUse = tileGID - tileSetToUse->getFirstGID();

			// ������������� TextureRect ������� �����
            if (subRectToUse >= 0)
            {
                sf::Sprite sprite;
                sprite.setTexture(tileSetToUse->tilesetTexture);
				sprite.setTextureRect(tileSetToUse->subRects[subRectToUse]);
                sprite.setPosition(x * tileWidth, y * tileHeight);
               // sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

                layer.tiles.push_back(sprite);
            }
            
                tileElement = tileElement->NextSiblingElement("tile");
            x++;
            if (x >= width)
            {
                x = 0;
                y++;
                if(y >= height)
                    y = 0;
            }
        }

        layers.push_back(layer);
        layerElement = layerElement->NextSiblingElement("layer");
        
    }

    // ������ � ���������
    XMLElement *objectGroupElement;

	// ���� ���� ���� ��������
    if (map->FirstChildElement("objectgroup") != NULL)
    {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement)
        {
			// ��������� <object>
            XMLElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");
           
			while(objectElement)
            {
				// �������� ��� ������ - ���, ���, �������, etc
                std::string objectType;
                if (objectElement->Attribute("type") != NULL)
                {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != NULL)
                {
                    objectName = objectElement->Attribute("name");
                }
                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));

				int width, height;

				sf::Sprite sprite;
                sprite.setTexture(tilesetImage);
				sprite.setTextureRect(sf::Rect<int>(0,0,0,0));
                sprite.setPosition(x, y);

				if (objectElement->Attribute("width") != NULL)
				{
					width = atoi(objectElement->Attribute("width"));
					height = atoi(objectElement->Attribute("height"));
				}

				// ��������� �������
                Object object;
                object.name = objectName;
                object.type = objectType;
				object.sprite = sprite;

                sf::Rect <int> objectRect;
                objectRect.top = y;
                objectRect.left = x;
				objectRect.height = height;
				objectRect.width = width;
                object.rect = objectRect;

				// "����������" �������
                XMLElement *properties;
                properties = objectElement->FirstChildElement("properties");
                if (properties != NULL)
                {
                    XMLElement *prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != NULL)
                    {
                        while(prop)
                        {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

				// ������ ������ � ������
                objects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else
    {
        std::cout << "No object layers found..." << std::endl;
    }

    return true;
}

Object* Level::GetObject(std::string name)
{
    Object* obj = nullptr;
	// ������ ������ ������ � �������� ������
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i].name == name)
            obj = &objects[i];
    }
    return obj;
}

std::vector<Object> Level::GetObjects(std::string name)
{
	// ��� ������� � �������� ������
	std::vector<Object> vec;
    for(int i = 0; i < objects.size(); i++)
        if(objects[i].name == name)
			vec.push_back(objects[i]);

	return vec;
}

sf::Vector2i Level::GetTileSize()
{
	return sf::Vector2i(tileWidth, tileHeight);
}

void Level::Draw(sf::RenderWindow &window)
{
	// ������ ��� ����� (������� �� ������!)
	for(int layer = 0; layer < layers.size(); layer++)
		for(int tile = 0; tile < layers[layer].tiles.size(); tile++)
			window.draw(layers[layer].tiles[tile]);
}

int tileSet::getFirstGID()
{
    return firstGID;
}

void tileSet::setImage(std::string _src)
{
    if (!image.loadFromFile(_src))
    {
        std::cout << "Bad image source" << std::endl;
    }
    else
    {
       // image.createMaskFromColor(sf::Color(109, 159, 185));
    }
    setTexture();
    
}

void tileSet::setTexture()
{
    tilesetTexture.loadFromImage(image);
    tilesetTexture.setSmooth(false);
    columns = tilesetTexture.getSize().x / tileWidth;
    rows = tilesetTexture.getSize().y / tileHeight;

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < columns; x++)
        {
            sf::Rect<int> rect;

            rect.top = y * tileHeight;
            rect.height = tileHeight;
            rect.left = x * tileWidth;
            rect.width = tileWidth;

            subRects.push_back(rect);
        }
}
