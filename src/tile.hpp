#ifndef TILE_HH
#define TILE_HH

#include "item.hpp"

struct Tile
{
    bool storeable;
    unsigned puzzlekey;

    std::string tooltip;
    std::string texname;
    
    Item storage;
    Item puzzlepiece;

    sf::Texture texture;
    sf::Sprite sprite;
};

#endif /* TILE_HH */
