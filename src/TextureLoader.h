#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>

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
    /*This is used to bind mutliple animations to 1 texture, 
    Because animation_pool map keys are identical to texture map keys
    Pretty hacky so it has to be changed. */
    static const sf::Texture& bindTexOnMultAnim(std::string texture_name, const sf::Texture& existing_texture_in_map)
    {
        if(textures.find(texture_name) != textures.end())
        {
            std::cerr << "There is already a texture with such name!\n";
        }
        textures[texture_name] = existing_texture_in_map;
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