//
// Created by Justin Galin on 11/9/22.
//

#ifndef PROJECT3_MINESWEEPER_BOARD_H
#define PROJECT3_MINESWEEPER_BOARD_H

#include "Tile.h"
#include "Random.h"
#include <vector>
#include <fstream>
#include <map>
using namespace std;


class Board {
public:
    vector<vector<Tile>> board;
    map<string, sf::Sprite> sprites;
    //std::vector<std::vector<std::shared_ptr<sf::Sprite>>> board;
    int columns;
    int width;
    int height;
    int rows;
    int num_mines;
    int tile_count;
    // THESE ARE HARD CODED AND NEED TO CHANGE
    int dig1 = 1;
    int dig2 = 0;
    int dig3  = 1;
    bool dig_neg = false;
    float dig_width = 21;
    int temp1 = 0;
    int boardnum = 0;
    bool once = true;
    int end_win = 0;
    int revealed = 0;
    bool game_win = false;
    float xpos = 400;
    float ypos = 200;
    float spacing = 96.5;
    Board();
    vector<vector<Tile>> GetBoard();
    int GetColumns();
    int GetRows();
    void MakeBoard(sf::RenderWindow &window);
    void DrawNum(sf::RenderWindow &window,int &num);
    void Flag(Tile &tile, sf::RenderWindow &window);
    void ResetBoard();
    void RandomBombs();
    void ResetCounter();
};


#endif //PROJECT3_MINESWEEPER_BOARD_H
