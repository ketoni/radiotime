#ifndef TILE_HH
#define TILE_HH

#include "item.hpp"

struct Tile
{
    bool storeable;
    unsigned puzzlekey;

    Item storage;
    Item puzzlepiece;
};

#endif /* TILE_HH */
