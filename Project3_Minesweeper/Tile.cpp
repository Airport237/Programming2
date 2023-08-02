//
// Created by Justin Galin on 11/9/22.
//
#include "Tile.h"

Tile::Tile(string texture_name_){
    texture_name = texture_name_;
    sf::Sprite tile_sprite_(TextureManager::GetTexture(texture_name));
    tile_sprite_.scale(1.5,1.5);
    tile_sprite = tile_sprite_;
}

void Tile::SetPosition(int x, int y){
    x_pos = x;
    y_pos = y;
    tile_sprite.setPosition(x,y);
}

void Tile::draw(sf::RenderWindow &window){
    if (l_clicked == false)
    {
        sf::Sprite reset(TextureManager::GetTexture("tile_hidden"));
        reset.setPosition(x_pos, y_pos);
        reset.scale(1.5,1.5);
        tile_sprite = reset;
        window.draw(tile_sprite);
        if (r_clicked == true)
        {
            sf::Sprite flag(TextureManager::GetTexture("flag"));
            flag.scale(1.5,1.5);
            flag.setPosition(x_pos,y_pos);
            window.draw(flag);

        } else if (show_bomb == false)
        {
            sf::Sprite reset(TextureManager::GetTexture("tile_hidden"));
            reset.setPosition(x_pos, y_pos);
            reset.scale(1.5,1.5);
            tile_sprite = reset;
            window.draw(tile_sprite);
        }
    }
    if (show_bomb == true)
    {
        is_revealed = true;
        sf::Sprite hidden(TextureManager::GetTexture("tile_hidden"));
        hidden.setPosition(x_pos, y_pos);
        hidden.scale(1.5,1.5);
        tile_sprite = hidden;
        window.draw(tile_sprite);


        if (flagbool == true)
        {
            sf::Sprite flag(TextureManager::GetTexture("flag"));
            flag.scale(1.5,1.5);
            flag.setPosition(x_pos,y_pos);
            window.draw(flag);
        }
        sf::Sprite bomb(TextureManager::GetTexture("mine"));
        bomb.setPosition(x_pos, y_pos);
        bomb.scale(1.5,1.5);
        tile_sprite = bomb;
        window.draw(tile_sprite);
    }

    if (l_clicked == true)
    {
        is_revealed = true;
        sf::Sprite reveal(TextureManager::GetTexture("tile_revealed"));
        reveal.setPosition(x_pos, y_pos);
        reveal.scale(1.5,1.5);
        tile_sprite = reveal;
        window.draw(tile_sprite);

        //Count the number of neighboring bombs

        if (is_bomb == true)
        {
            sf::Sprite bomb(TextureManager::GetTexture("mine"));
            bomb.setPosition(x_pos, y_pos);
            bomb.scale(1.5,1.5);
            tile_sprite = bomb;
            window.draw(tile_sprite);
        } else if (neighborBombs > 0)
        {
            if (neighborBombs == 1)
            {
                sf::Sprite number(TextureManager::GetTexture("number_1"));
                number.setPosition(x_pos, y_pos);
                number.scale(1.5,1.5);
                tile_sprite = number;
                window.draw(tile_sprite);
            } else if (neighborBombs == 2)
            {
                sf::Sprite number(TextureManager::GetTexture("number_2"));
                number.setPosition(x_pos, y_pos);
                number.scale(1.5,1.5);
                tile_sprite = number;
                window.draw(tile_sprite);
            }else if (neighborBombs == 3)
            {
                sf::Sprite number(TextureManager::GetTexture("number_3"));
                number.setPosition(x_pos, y_pos);
                number.scale(1.5,1.5);
                tile_sprite = number;
                window.draw(tile_sprite);
            }else if (neighborBombs == 4)
            {
                sf::Sprite number(TextureManager::GetTexture("number_4"));
                number.setPosition(x_pos, y_pos);
                number.scale(1.5,1.5);
                tile_sprite = number;
                window.draw(tile_sprite);
            }else if (neighborBombs == 5)
            {
                sf::Sprite number(TextureManager::GetTexture("number_5"));
                number.setPosition(x_pos, y_pos);
                number.scale(1.5,1.5);
                tile_sprite = number;
                window.draw(tile_sprite);
            }else if (neighborBombs == 6)
            {
                sf::Sprite number(TextureManager::GetTexture("number_6"));
                number.setPosition(x_pos, y_pos);
                number.scale(1.5,1.5);
                tile_sprite = number;
                window.draw(tile_sprite);
            }else if (neighborBombs == 7)
            {
                sf::Sprite number(TextureManager::GetTexture("number_7"));
                number.setPosition(x_pos, y_pos);
                number.scale(1.5,1.5);
                tile_sprite = number;
                window.draw(tile_sprite);
            }else if (neighborBombs == 8)
            {
                sf::Sprite number(TextureManager::GetTexture("number_8"));
                number.setPosition(x_pos, y_pos);
                number.scale(1.5,1.5);
                tile_sprite = number;
                window.draw(tile_sprite);
            }

        }


    }
//    if (show_bomb == false)
//    {
//        sf::Sprite reset(TextureManager::GetTexture("tile_hidden"));
//        reset.setPosition(x_pos, y_pos);
//        reset.scale(1.5,1.5);
//        tile_sprite = reset;
//        window.draw(tile_sprite);
//
//    }

}

sf::FloatRect Tile::getBounds()
{
    return tile_sprite.getGlobalBounds();
}

void Tile::PlaceFlag() {
    r_clicked = !r_clicked;
    flagbool = !flagbool;
}

void Tile::ClearTiles(sf::RenderWindow &window)
{
    for(int k = 0; k < neighbors.size(); k++)
    {
        if(neighbors[k]->is_bomb == false and is_bomb == false and neighbors[k]->is_revealed == false and neighbors[k]->flagbool == false)
        {
            neighbors[k]->l_clicked = true;
            neighbors[k]->is_revealed = true;
            neighbors[k]->draw(window);
            if(neighbors[k]->NeighborsClear())
            {
                neighbors[k]->ClearTiles(window);
            }
        }
    }
}


bool Tile::NeighborsClear()
{
    bool clear = true;
    for(int l = 0; l < neighbors.size(); l++)
    {
        if(neighbors[l]->is_bomb == true)
        {
            clear = false;
        }
    }
    return clear;
}