#ifndef TILE_H
#define TILE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "tile.hpp"
#include "item.hpp"
#include <vector>

class Tile
{
public:
	Tile();
  ~Tile();

  Item* item;

};

#endif /* TILE_H */
