//
// Created by Justin Galin on 11/9/22.
//

#include "TextureManager.h"

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(std::string fileName)
{
    string path = "images/";
    path += fileName;
    path += ".png";

    textures[fileName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string textureName)
{
    if (textures.find(textureName) == textures.end()) //Not in map
        LoadTexture(textureName);

    return textures[textureName];
}

void TextureManager::Clear()
{
    textures.clear();
}