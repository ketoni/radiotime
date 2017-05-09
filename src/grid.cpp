#include "grid.hpp"

Grid::Grid(unsigned int width, unsigned int height){

	this->width = width;
	this->height = height;

	for(unsigned int y = 0; y < height; y++){

		std::vector<Tile*> row;

		for(unsigned int x = 0; x < width; x++){

			Tile* tile;
			row.push_back(tile);
		}

		tiles.push_back(row);
	}
}
