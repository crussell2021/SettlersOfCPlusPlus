#ifndef TILE_H
#define TILE_H

#include "hexLoc.h"

//enum tileType {sand, wood, brick, sheep, wheat, rock};

class Tile {
public:
	Tile();
	Tile(cube_t cube);

	int getType() { return resource; }
	void setType(int resource) { this->resource = resource; }
	int getNumber() { return number; }
	void setNumber(int num) { this->number = num; }

	cube_t getHexCoords();
	void setHexCoords(cube_t);
	coords_t getTileCenter(int tileSize);

	cube_t getNeighbor(int direction);

private:
	cube_t hexCoords;
	int number;
	int resource;
};

#endif