#include "Board.h"
int main()
{
    //Sets up game window and board
    sf::RenderWindow window(sf::VideoMode(2000,1500), "Minesweeper");
    Board b;
    bool flipped2 = false;
    bool tem=false;

    //Main Program Loop
    while(window.isOpen())
    {
        // Creating event loop to do things when mouse is clicked
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseButtonPressed)
            {
                //Places flag with right click
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    bool flipped = false;
                    for (int i = 0; i < b.GetRows(); i++)
                    {
                        for (int j = 0; j < b.GetColumns(); j++)
                        {
                            sf::Vector2i coordinates =  sf::Mouse::getPosition(window);
                            if (b.board[i][j].getBounds().contains(coordinates.x, coordinates.y) and flipped == false and b.board[i][j].end_game == false and b.game_win == false)
                            // Includes and statement to make sure that two flags aren't placed with one click
                            {
                                b.Flag(b.board[i][j], window);
                                b.board[i][j].draw(window);
                                flipped = true;
                            }
                        }
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    bool flipped = false;
                    sf::Vector2i coordinates = sf::Mouse::getPosition(window);
                    for (int i = 0; i < b.GetRows(); i++)
                    {
                        for (int j = 0; j < b.GetColumns(); j++)
                        {
                            // And statements to make sure you can only click something that isnt flagged and isnt clicked
                            if (b.board[i][j].getBounds().contains(coordinates.x, coordinates.y) and flipped == false and b.board[i][j].flagbool == false and b.board[i][j].is_revealed == false and b.board[i][j].end_game == false)
                                // Includes and statement to make sure that two flags aren't placed with one click
                            {
                                b.board[i][j].l_clicked = true;
                                b.board[i][j].draw(window);
                                if(b.board[i][j].NeighborsClear())
                                {
                                    b.board[i][j].ClearTiles(window);
                                }
                                flipped = true;
                                //Condition for LOSS
                                if (b.board[i][j].is_bomb)
                                {
                                    for (int i = 0; i < b.GetRows(); i++)
                                    {
                                        for (int j = 0; j < b.GetColumns(); j++)
                                        {
                                            if(b.board[i][j].is_bomb)
                                            {
                                                b.board[i][j].l_clicked = true;
                                                b.board[i][j].draw(window);
                                            }
                                            b.board[i][j].end_game = true;
                                        }
                                    }
                                }
                                }
                            }
                        }
                    if (b.sprites["debug"].getGlobalBounds().contains(coordinates.x, coordinates.y) and b.game_win == false)
                    {
                        for (int i = 0; i < b.GetRows(); i++)
                        {
                            for (int j = 0; j < b.GetColumns(); j++)
                            {
                                if (b.board[i][j].is_bomb == true)
                                {
                                    if (flipped2 == false)
                                    {
                                        b.board[i][j].show_bomb = true;
                                    } else
                                    {
                                        b.board[i][j].show_bomb = false;
                                        b.board[i][j].is_revealed = false;
                                    }
                                }
                            }
                        }
                        if (flipped2 == false)
                        {
                            flipped2 = true;

                        }else{
                            flipped2 = false;
                        }
                    }
                    if (b.sprites["face"].getGlobalBounds().contains(coordinates.x, coordinates.y))
                    {
                        b.boardnum = 0;
                        b.ResetBoard();
                        b.MakeBoard(window);
                        b.RandomBombs();
                        b.ResetCounter();

                    }
                    if (b.sprites["test1"].getGlobalBounds().contains(coordinates.x, coordinates.y))
                    {
                        b.boardnum = 1;
                        b.ResetBoard();
                        b.once = true;
                        b.MakeBoard(window);

                    }
                    if (b.sprites["test2"].getGlobalBounds().contains(coordinates.x, coordinates.y))
                    {
                        b.boardnum = 2;
                        b.ResetBoard();
                        b.once = true;
                        b.MakeBoard(window);
                    }
                    if (b.sprites["test3"].getGlobalBounds().contains(coordinates.x, coordinates.y))
                    {
                        b.boardnum = 3;
                        b.ResetBoard();
                        b.once = true;
                        b.MakeBoard(window);
                    }
                }
            }
        }
        window.clear(sf::Color::White);
        //Sets up intitial board

        b.MakeBoard(window);
        if(tem == false)
        {
            b.RandomBombs();
            tem = true;
            b.ResetCounter();
        }
        window.display();
    }
    // Cleans up textures map from the TextureManager Class
    TextureManager::Clear();
    return 0;
}