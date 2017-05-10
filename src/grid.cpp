#include "grid.hpp"

Grid::Grid() : _width(5), _height(5), _tilesize(40) {

    _tiles.assign({
        #include "tiledef"
    });        

    initTiles();
}

void Grid::initTiles()
{
    unsigned x = 0, y = 0;

    for (auto& tile : _tiles) {

        if (tile.texname.length()) {
            // Load a texture to the tile and initialize the sprite
            tile.texture.loadFromFile(tile.texname);
            tile.sprite = sf::Sprite(tile.texture);

            // Also move the sprite to the correct position on the screen
            tile.sprite.move(x*_tilesize, y*_tilesize);
        }
        if (++x == _width) {
            x = 0;
            ++y;
        }
    }
}

unsigned Grid::getWidth()
{
    return _width;
}

unsigned Grid::getHeight()
{
    return _height;
}

std::vector<Tile> const& Grid::getTiles()
{
    return _tiles;
}
