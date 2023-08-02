//
// Created by Justin Galin on 11/9/22.
//
#pragma once

#include "Tile.h"
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;



class TextureManager {
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(string textureName); // LoadTexture(mine)
public:
    static sf::Texture& GetTexture(string textureName);
    static void Clear(); // Call once at end of main()

};


