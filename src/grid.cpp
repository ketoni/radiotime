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
        
            tile.storage.texture.loadFromFile(tile.storage.texname);
            tile.storage.sprite = sf::Sprite(tile.storage.texture);

            // Also move the sprites to the correct position on the screen
            tile.sprite.move(x*_tilesize, y*_tilesize);
            tile.storage.sprite.move(x*_tilesize, y*_tilesize);
        }
        if (++x == _width) {
            x = 0;
            ++y;
        }
    }
}

bool Grid::canMoveTo(int x, int y)
{
    int idx = y * _width + x;
    if (x >= 0 && x < _width && y >= 0 && y < _height) {
        return !bool(_tiles.at(idx).texname.length());
    } 
    return false;
}

bool Grid::canInteractWith(int x, int y)
{
    int idx = y * _width + x;
    if (x >= 0 && x < _width && y >= 0 && y < _height) {
        return _tiles.at(idx).storeable;
    } 
    return false;
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

Tile& Grid::getTile(unsigned x, unsigned y) {
    int idx = y * _width + x;
    return _tiles.at(idx);
}
