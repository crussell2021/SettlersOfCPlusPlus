#ifndef TILE_H
#define TILE_H

#include "display.h"	//for coords_t struct

enum tileType {sand, wood, brick, sheep, wheat, rock};

//a convinient way to store hex coorinates, see https://www.redblobgames.com/grids/hexagons/ for reference
struct cube_t {
	int x;
	int y;
	int z;
};

class Tile {
public:
	Tile();
	Tile(int x, int y, int z);
	Tile(cube_t cube);

	tileType getType() { return resource; }
	void setType(tileType resource) { this->resource = resource; }
	int getNumber() { return number; }
	void setNumber(int num) { this->number = num; }

	cube_t getHexCoords();
	void setHexCoordinates(cube_t);
	coords_t getTileCenter(int tileSize);

	static coords_t getTileCenter(cube_t tile, int tileSize = 64);		//numbers divisable by 8 will work best in calcualtion, becasue coords are stored as ints, not floats
	static coords_t getPosOffset(int position, int tileSize = 64);

	cube_t getNeighbor(int direction);
	static cube_t getNeighbor(cube_t coords, int direction);

private:
	int x;
	int y;
	int z;
	int number;
	tileType resource;
};

#endif