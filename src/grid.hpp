#ifndef GRID_H
#define GRID_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "tile.hpp"
#include <vector>

class Grid
{
    public:
        Grid();

        unsigned getWidth();
        unsigned getHeight();

        std::vector<Tile> const& getTiles();
        Tile& getTile(unsigned, unsigned);

        bool canMoveTo(int, int);
        bool canInteractWith(int, int);

    private:
        void initTiles();

        std::vector<Tile> _tiles;

        unsigned _width;
        unsigned _height;

        unsigned _tilesize;
};

#endif /* GRID_H */
