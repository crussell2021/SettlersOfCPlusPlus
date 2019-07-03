#ifndef IMPROVEMENT_H
#define IMPROVEMENT_H

#include "tile.h"

class Improvement {
public:
	Improvement();
	Improvement(cube_t coords, int corner, bool city=false);
	Improvement(HexLoc location, bool city=false);

	int getX() { return hexLoc.getHexCoords().x; }
	int getY() { return hexLoc.getHexCoords().y; }
	int getZ() { return hexLoc.getHexCoords().z; }
	int getCorner() { return hexLoc.getPos(); }
	
	void buildCity();
	coords_t getCenter(int tileSize);
	cube_t getTile(int tileIndex) { return tileArray[tileIndex]; }
	HexLoc getHexLoc() { return hexLoc; }

	bool isCornerOpen(cube_t tile, int corner);
	bool isLocationOpen(HexLoc location);
	HexLoc getLocation() { return hexLoc; }
		
private:
	bool typeCity;				//false for settlement, true for city
	cube_t tileArray[3];			//any Improvement will be at the intersection of 3 tiles
	HexLoc adjacentCorners[3];
	HexLoc hexLoc;				//location
};

#endif