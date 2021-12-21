#include "TextureLoader.h"


std::map<std::string,sf::Texture> TextureLoader::textures = {};

const sf::Texture& TextureLoader::loadFromImage(const sf::Image& image, std::string texture_name) {
    
        sf::Texture texture;
        texture.loadFromImage(image);
        textures[texture_name] = std::move(texture);

        return textures[texture_name];
    
}

const sf::Texture& TextureLoader::getTexture(const std::string& name) {

    auto texture_it = textures.find(name);

    if(texture_it != textures.end())
    {
        return texture_it->second;
    }
    std::cerr << "There is no texture loaded with that name! (" << name << ")\n";
}

const sf::Texture& TextureLoader::bindTexOnMultAnim(const std::string texture_name, const sf::Texture& existing_texture_in_map) {
    
    if(textures.find(texture_name) != textures.end())
    {
        std::cerr << "There is already a texture with such name!\n";
    }
    textures[texture_name] = existing_texture_in_map;
}

const sf::Texture& TextureLoader::loadFromFile(const std::string filename, std::string texture_name) {

    sf::Texture texture;
    texture.loadFromFile(filename);
    textures[texture_name] = std::move(texture);

}
