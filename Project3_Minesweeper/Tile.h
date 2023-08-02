//
// Created by Justin Galin on 11/9/22.
//

#ifndef PROJECT3_MINESWEEPER_TILE_H
#define PROJECT3_MINESWEEPER_TILE_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"


using std::cout;
using std::endl;
using std::string;

class Tile {
    string texture_name;
    bool is_num = false;

public:
    std::vector<Tile*> neighbors;
    sf::Sprite tile_sprite;
    int x_pos = 0;
    int y_pos = 0;
    int neighborBombs = 0;
    bool is_revealed = false;
    bool is_bomb = false;
    bool flagbool = false;
    bool show_bomb = false;
    bool l_clicked = false;
    bool r_clicked = false;
    bool end_game = false;
    Tile(string texture_name_);
    void SetPosition(int x, int y);
    void draw(sf::RenderWindow &window);
    sf::FloatRect getBounds();
    void PlaceFlag();
    void ClearTiles(sf::RenderWindow &window);
    bool NeighborsClear();
};


#endif //PROJECT3_MINESWEEPER_TILE_H
