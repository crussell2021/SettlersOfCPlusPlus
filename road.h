#ifndef ROAD_H
#define ROAD_H

#include "tile.h"
#include "hexLoc.h"

class Road {
public: 
	Road();
	Road(cube_t tile, int corner1, int corner2);

	bool checkCorner(cube_t tile, int corner);
	bool containsCorner(HexLoc location);

	Tile getTile() { return Tile(tile); }
	int getCorner(int index) { return corner[index]; }
	int getDirection() { return direction; }
	int getLocation() { return location; }
	coords_t getImageLocation(int tileSize);
private:
	int corner[2];
	HexLoc locationCorners[2];
	cube_t tile;
	int direction;		//image direction
	int location;		//location in tile
};

#endif