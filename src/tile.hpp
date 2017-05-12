#ifndef TILE_HH
#define TILE_HH

#include "item.hpp"

struct Tile
{
    bool storeable;
    bool hidden;
    int puzzlekey;

    std::string tooltip;
    std::string texname;
    
    Item storage;
    Item puzzlepiece;
    
    std::string puzzlehint;

    sf::Sprite sprite;
};

#endif /* TILE_HH */
