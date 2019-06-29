#ifndef CATANBOARD_H
#define CATANBOARD_H

#include <time.h>
#include "tile.h"
//#include "HexLoc.h"

class CatanBoard {
public:
	CatanBoard(int size);	//constructor

	void createTileRing(int radius);
	void createTileSpiral(int radius);

	coords_t getTileCenter(int index, int tileSize);
	coords_t getCornerCoords(int index, int corner, int tileSize);
	static coords_t getCornerCoords(cube_t tile, int corner, int tileSize);

	coords_t getBorderCoords(int index, int tileSize);

	cube_t getTileByIndex(int index) { return tiles[index].getHexCoords(); }
	int getTileByCoords(cube_t tile);

	tileType getTileType(int index) { return tiles[index].getType(); }
	void loadTileTypes();
	void randomizeTileType();

	int getTileNumber(int index) { return tiles[index].getNumber(); }
	void loadTileNumbers(int extra1 = 2, int extra2 = 12);
	void randomizeTileNumbers();

	int getNumberOfTiles() { return numberOfTiles; }

	tileType getResourceAt(int index) { return tiles[index].getType(); }
private:
	void newTile(cube_t coords);
	Tile* tiles;
	int numberOfTiles;
	int maxNumberOfTiles;	
	int size;
};

#endif