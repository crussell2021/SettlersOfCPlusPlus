#ifndef ROAD_H
#define ROAD_H

#include "tile.h"

class Road {
public: 
	Road();
	Road(cube_t tile, int corner1, int corner2);
	Road(HexLoc loc1, HexLoc loc2);

	bool containsCorner(HexLoc location);

	int getX() { return locationCorners[0].getHexCoords().x; }
	int getY() { return locationCorners[0].getHexCoords().y; }
	int getZ() { return locationCorners[0].getHexCoords().z; }
	int getCorner(int index) { return corner[index]; }
	
	int getOrientation() { return orientation; }
	int getLocation() { return location; }
	coords_t getImageLocation(int tileSize);
private:
	int corner[2];
	HexLoc locationCorners[2];
	int orientation;		//image orientation
	int location;		//location in tile
};

#endif