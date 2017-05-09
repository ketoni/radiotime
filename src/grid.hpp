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
	Grid(unsigned int width, unsigned int height);
  ~Grid();

  std::vector<std::vector<Tile*>> tiles;
  unsigned int width;
  unsigned int height;

};

#endif /* GRID_H */
