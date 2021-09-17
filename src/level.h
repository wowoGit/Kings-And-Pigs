#ifndef LEVEL_H
#define LEVEL_H

//#pragma comment(lib,"Box2D.lib")
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-system.lib")
#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>


struct Object
{
    int GetPropertyInt(std::string name);
    float GetPropertyFloat(std::string name);
    std::string GetPropertyString(std::string name);

    std::string name;
    std::string type;
    sf::Rect<int> rect;
    std::map<std::string, std::string> properties;
    
	sf::Sprite sprite;
};


struct tileSet
{
    int getFirstGID();
    void setImage(std::string _src);
    void setTexture();
    int firstGID;
    int rows;
    int columns;
    int tileHeight;
    int tileWidth;
    std::vector<sf::Rect<int>> subRects;
    sf::Image image;
    sf::Texture tilesetTexture;
};
struct Layer
{
    int opacity;
    std::vector<sf::Sprite> tiles;
};

class Level
{
public:
    bool LoadFromFile(std::string filename);
    Object* GetObject(std::string name);
    std::vector<Object> GetObjects(std::string name);
    void Draw(sf::RenderWindow &window);
	sf::Vector2i GetTileSize();

private:
    int width, height, tileWidth, tileHeight;
    int firstTileID;
    sf::Rect<float> drawingBounds;
    sf::Texture tilesetImage;
    std::vector<Object> objects;
    std::vector<Layer> layers;
};

#endif
