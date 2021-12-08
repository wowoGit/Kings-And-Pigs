#pragma once
#include <map>
#include <SFML/Graphics.hpp>

class TextureLoader
{
    public:


    static const sf::Texture& loadFromFile(std::string filename, std::string texture_name) 
    {

        sf::Texture texture;
        texture.loadFromFile(filename);
        textures[texture_name] = std::move(texture);

        return textures[texture_name];
    }
    static const sf::Texture& loadFromImage(const sf::Image& image, std::string texture_name) 
    {
        sf::Texture texture;
        texture.loadFromImage(image);
        textures[texture_name] = std::move(texture);

        return textures[texture_name];
    }

    static const sf::Texture& getTexture(std::string name)
    {
        return textures[name];
    }

    private:
    static std::map<std::string,sf::Texture> textures;


};