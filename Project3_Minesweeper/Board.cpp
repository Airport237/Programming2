//
// Created by Justin Galin on 11/9/22.
//

#include "Board.h"


Board::Board() {

}

void Board::MakeBoard(sf::RenderWindow &window){
    std::ifstream file("boards/config.cfg");
    std::ifstream test_file;
    if(boardnum == 1)
    {
        test_file.open("boards/testboard1.brd");
    } else if(boardnum == 2)
    {
        test_file.open("boards/testboard2.brd");
    } else if(boardnum == 3)
    {
        test_file.open("boards/testboard3.brd");
    }
    if (file.is_open())
    {
        // Import config data
        int num;
        file >> num;
        columns = num;
        width = columns*32;
        file >> num;
        rows = num;
        height = rows*32 + 100;
        file >> num;
        num_mines = num;
        tile_count = columns*rows;

        //NEED TO ADD CONDIRIONS TO CHANGE ONCE VARIABLE IN BUTTONS THAT RELOAD MAPS SINCE AMOUNT OF BOMBS WILL CHANGE


        //Setup Tile Vector
        Tile tile("tile_hidden");
        vector<Tile> temp;

        for (int i = 0; i < columns; i++)
        {
            temp.push_back(tile);
        }
        for (int i = 0; i < rows; i++)
        {
            board.push_back(temp);
        }
        //Draws all the tiles in the vector onto the screen

        for(int i = 0; i < GetRows(); i++)
        {
            for(int j = 0; j < GetColumns(); j++)
            {
                char bomb;
                if(boardnum > 0)
                {
                    test_file >> bomb;
                    if (i == 0 and j == 0)
                    {
                        num_mines = 0;
                    }
                }
                if (bomb == '1')
                {
                    board[i][j].is_bomb = true;
                    num_mines++;
                }
                //Numbers are hard coded for now until I make a proper way to show the window
                board[i][j].SetPosition(xpos+j*45,ypos+i*45);
                board[i][j].draw(window);
                //Assign Tile Neighbors
                //Top Edge
                if (i == 0)
                {
                    //Top Left Corner
                    if (j == 0)
                    {
                        board[i][j].neighbors.push_back(&board[i+1][j]);
                        board[i][j].neighbors.push_back(&board[i][j+1]);
                        board[i][j].neighbors.push_back(&board[i+1][j+1]);
                    }
                    //Top Right Corner
                    else if (j == GetColumns()-1)
                    {
                        board[i][j].neighbors.push_back(&board[i+1][j]);
                        board[i][j].neighbors.push_back(&board[i][j-1]);
                        board[i][j].neighbors.push_back(&board[i+1][j-1]);
                    }
                    else if (j > 0 and j < (GetColumns()-1))
                    {
                        board[i][j].neighbors.push_back(&board[i][j-1]);
                        board[i][j].neighbors.push_back(&board[i][j+1]);
                        board[i][j].neighbors.push_back(&board[i+1][j-1]);
                        board[i][j].neighbors.push_back(&board[i+1][j]);
                        board[i][j].neighbors.push_back(&board[i+1][j+1]);
                    }
                }
                //Bottom Edge
                else if (i == GetRows()-1)
                {
                    //Bottom Left Corner
                    if (j == 0)
                    {
                        board[i][j].neighbors.push_back(&board[i-1][j]);
                        board[i][j].neighbors.push_back(&board[i][j+1]);
                        board[i][j].neighbors.push_back(&board[i-1][j+1]);
                    }
                    //Bottom Right Corner
                    if (j == GetColumns()-1)
                    {
                        board[i][j].neighbors.push_back(&board[i-1][j]);
                        board[i][j].neighbors.push_back(&board[i][j-1]);
                        board[i][j].neighbors.push_back(&board[i-1][j-1]);
                    }
                    else if (j > 0 and j < (GetColumns()-1))
                    {
                        board[i][j].neighbors.push_back(&board[i][j-1]);
                        board[i][j].neighbors.push_back(&board[i][j+1]);
                        board[i][j].neighbors.push_back(&board[i-1][j-1]);
                        board[i][j].neighbors.push_back(&board[i-1][j]);
                        board[i][j].neighbors.push_back(&board[i-1][j+1]);
                    }
                }
                //Left Edge
                else if(j == 0 and i > 0 and i < (GetRows()-1))
                {
                    //FIX INDEXES AND THEN RIGHT EDGE AND THEN ALL THE MIDDLE
                    board[i][j].neighbors.push_back(&board[i-1][j]);
                    board[i][j].neighbors.push_back(&board[i-1][j+1]);
                    board[i][j].neighbors.push_back(&board[i][j+1]);
                    board[i][j].neighbors.push_back(&board[i+1][j+1]);
                    board[i][j].neighbors.push_back(&board[i+1][j]);
                }
                //Right Edge
                else if(j == (GetColumns()-1) and i > 0 and i < (GetRows()-1))
                {
                    board[i][j].neighbors.push_back(&board[i-1][j]);
                    board[i][j].neighbors.push_back(&board[i-1][j-1]);
                    board[i][j].neighbors.push_back(&board[i][j-1]);
                    board[i][j].neighbors.push_back(&board[i+1][j-1]);
                    board[i][j].neighbors.push_back(&board[i+1][j]);
                }
                //Anything not on the edge
                else if(i>0 and j>0 and i<(GetRows()-1) and j<(GetColumns()-1))
                {
                    board[i][j].neighbors.push_back(&board[i-1][j-1]);
                    board[i][j].neighbors.push_back(&board[i-1][j]);
                    board[i][j].neighbors.push_back(&board[i-1][j+1]);
                    board[i][j].neighbors.push_back(&board[i][j-1]);
                    board[i][j].neighbors.push_back(&board[i][j+1]);
                    board[i][j].neighbors.push_back(&board[i+1][j-1]);
                    board[i][j].neighbors.push_back(&board[i+1][j]);
                    board[i][j].neighbors.push_back(&board[i+1][j+1]);

                }
            }
        }
        if (boardnum > 0 and once == true)
        {
            ResetCounter();
            once = false;
        }

        if (temp1 == 0)
        {
            for(int k = 0; k < GetRows(); k++)
            {
                for(int l = 0; l < GetColumns(); l++)
                {
                    for(int m = 0; m < board[k][l].neighbors.size(); m++)
                    {
                        if(board[k][l].neighbors[m]->is_bomb == true)
                        {
                            board[k][l].neighborBombs++;
                        }
                    }
                }
            }
            temp1++;
        }

        //Draw num of mines
        sf::Sprite digits1(TextureManager::GetTexture("digits"));
        sf::Sprite digits2(TextureManager::GetTexture("digits"));
        sf::Sprite digits3(TextureManager::GetTexture("digits"));
        sf::Sprite neg(TextureManager::GetTexture("digits"));

//        sprites.emplace("digits1", &digits1);
//        sprites.emplace("digits2", &digits2);
//        sprites.emplace("digits3", &digits3);

        digits1.setTextureRect(sf::IntRect(dig_width*dig1, 0, dig_width, 32));
        digits1.setPosition(xpos + dig_width,ypos + GetRows()*45);
        //digits1.scale(1.5,1.5);
        window.draw(digits1);

        digits2.setTextureRect(sf::IntRect(dig_width*dig2, 0, dig_width, 32));
        digits2.setPosition(xpos + 2*dig_width,ypos + GetRows()*45);
        //digits2.scale(1.5,1.5);
        window.draw(digits2);

        //dig3 = 8;
        digits3.setTextureRect(sf::IntRect(dig_width*dig3, 0, dig_width, 32));
        digits3.setPosition(xpos + 3*dig_width,ypos + GetRows()*45);
        //digits3.scale(1.5,1.5);
        window.draw(digits3);

        if (dig_neg == true)
        {
            neg.setTextureRect(sf::IntRect(dig_width*10, 0, dig_width, 32));
            neg.setPosition(xpos,ypos + GetRows()*45);
            //digits3.scale(1.5,1.5);
            window.draw(neg);
        }

        int face_pos = xpos + GetColumns()*45*0.5;
        end_win = 0;
        revealed = 0;
        for(int i = 0; i < GetRows(); i++)
        {
            for (int j = 0; j < GetColumns(); j++)
            {
                if (board[i][j].is_bomb == true and board[i][j].flagbool == true)
                {
                    end_win++;
                } else if (board[i][j].is_revealed == true)
                {
                    revealed++;
                }
            }
        }


        if(board[0][0].end_game == false)
        {
            if (end_win == num_mines and revealed == GetRows()*GetColumns()-num_mines)
            {
                sf::Sprite face(TextureManager::GetTexture("face_win"));
                face.scale(1.5,1.5);
                face.setPosition(face_pos, ypos + GetRows()*45+ 3);
                window.draw(face);
                game_win = true;
            } else
            {
                sf::Sprite face(TextureManager::GetTexture("face_happy"));
                face.scale(1.5,1.5);
                face.setPosition(face_pos, ypos + GetRows()*45+ 3);
                window.draw(face);
                sprites.emplace("face", face);
            }

        } else if (board[0][0].end_game == true)
        {
            sf::Sprite face(TextureManager::GetTexture("face_lose"));
            face.scale(1.5,1.5);
            face.setPosition(face_pos, ypos + GetRows()*45+ 3);
            window.draw(face);
        }


        sf::Sprite debug(TextureManager::GetTexture("debug"));
        debug.scale(1.5,1.5);
        debug.setPosition(face_pos + spacing*2, ypos + GetRows()*45+ 3);
        window.draw(debug);
        sprites.emplace("debug", debug);

        sf::Sprite test1(TextureManager::GetTexture("test_1"));
        test1.scale(1.5,1.5);
        test1.setPosition(face_pos + spacing*3, ypos + GetRows()*45+ 3);
        window.draw(test1);
        sprites.emplace("test1", test1);

        sf::Sprite test2(TextureManager::GetTexture("test_2"));
        test2.scale(1.5,1.5);
        test2.setPosition(face_pos + spacing*4 , ypos + GetRows()*45+ 3);
        window.draw(test2);
        sprites.emplace("test2", test2);

        sf::Sprite test3(TextureManager::GetTexture("test_3"));
        test3.scale(1.5,1.5);
        test3.setPosition(face_pos + spacing*5 , ypos + GetRows()*45 + 3);
        window.draw(test3);
        sprites.emplace("test3", test3);
    }
}

vector<vector<Tile>>  Board::GetBoard()
{
    return board;
}

int Board::GetColumns() {
    return columns;
}

int Board::GetRows() {
    return rows;
}

void Board::Flag(Tile &tile, sf::RenderWindow &window){
    tile.PlaceFlag();
    if (dig3 != 0 and tile.flagbool == true and dig_neg == false)
    {
        dig3--;

    } else if (dig3 == 0 and tile.flagbool == true and dig2 > 0 and dig_neg == false)
    {
        dig2--;
        dig3 = 9;
    } else if (dig2 == 0 and dig3 == 0 and dig1 != 0 and tile.flagbool == true and dig1 > 0 and dig_neg == false)
    {
        dig1--;
        dig3 = 9;
        dig2 = 9;
    } else if(dig3 != 9 and tile.flagbool == false and dig_neg == false)
    {
        dig3++;

    } else if(dig3 == 9 and tile.flagbool == false and dig2 != 9 and dig_neg == false)
    {
        dig2++;
        dig3 = 0;
    } else if (dig2 == 9 and dig3 == 9 and tile.flagbool == false and dig_neg == false)
    {
        dig1++;
        dig3 = 0;
        dig2 = 0;
    }
    //Logic for negative mines
    else if (dig1 == 0 and dig2 == 0 and dig3 == 0 and tile.flagbool == true and dig_neg == false)
    {
        dig_neg = true;
        dig3++;
    } else if (dig1 == 0 and dig2 == 0 and dig3 == 1 and dig_neg == true and tile.flagbool == false)
    {
        dig_neg = false;
        dig3 = 0;
    } else if (dig3 != 9 and tile.flagbool == true and dig_neg == true)
    {
        dig3++;

    } else if (dig3 == 9 and tile.flagbool == true and dig2 !=9 and dig_neg == true)
    {
        dig2++;
        dig3 = 0;
    } else if (dig2 == 9 and dig3 == 9 and tile.flagbool == true and dig_neg == true)
    {
        dig1++;
        dig3 = 0;
        dig2 = 0;
    } else if(dig3 != 0 and tile.flagbool == false and dig_neg == true)
    {
        dig3--;

    } else if(dig3 == 0 and tile.flagbool == false and dig2 != 0 and dig_neg == true)
    {
        dig2--;
        dig3 = 9;
    } else if (dig2 == 0 and dig3 == 0 and dig1 != 0 and tile.flagbool == false and dig_neg == true)
    {
        dig1--;
        dig3 = 9;
        dig2 = 9;
    }
}

void Board::ResetBoard()
{
    temp1 = 0;
    game_win = false;
    dig_neg = false;
    board = {};
}

void Board::RandomBombs()
{
    int bcount = 0;
    //Loop until mines reach what they're suppose dot be
    while(bcount < num_mines)
    {
        //Generate random index
        int indexC = Random::Int(0,GetColumns()-1);
        int indexR = Random::Int(0,GetRows()-1);
        // If its not already a mine make it a mine
        if(board[indexR][indexC].is_bomb == false)
        {
            board[indexR][indexC].is_bomb = true;
            bcount++;
        }

    }
    //Reset neighbor bombs count
    for(int k = 0; k < GetRows(); k++)
    {
        for(int l = 0; l < GetColumns(); l++)
        {
            for(int m = 0; m < board[k][l].neighbors.size(); m++)
            {
                if(board[k][l].neighbors[m]->is_bomb == true)
                {
                    board[k][l].neighborBombs++;
                }
            }
        }
    }

}

void Board::ResetCounter()
{
    int counter = 0;
    int copy = num_mines;
    while (copy > 9)
    {
        if (counter == 0)
            dig3 = copy%10;
        if (counter == 1)
            dig2 = copy%10;
        copy = floor(copy/10);
        counter++;
    }
    //Case for last digit
    if (counter == 0)
    {
        dig3 = copy;
        dig2 = 0;
        dig1 = 0;
    }
    if (counter == 1)
    {
        dig2 = copy;
        dig1 = 0;
    }
    if (counter == 2)
        dig1 = copy;
}

