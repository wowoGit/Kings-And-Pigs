#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>

class TextureLoader
{
    public:


    static const sf::Texture& loadFromFile(std::string filename, std::string texture_name);
    /*This is used to bind mutliple animations to 1 texture, 
    Because animation_pool map keys are identical to texture map keys
    Pretty hacky so it has to be changed. */
    static const sf::Texture& bindTexOnMultAnim(std::string texture_name, const sf::Texture& existing_texture_in_map);
    static const sf::Texture& loadFromImage(const sf::Image&, std::string);

    static const sf::Texture& getTexture(const std::string&);

    private:
    static std::map<std::string,sf::Texture> textures;


};