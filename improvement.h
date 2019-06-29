#ifndef IMPROVEMENT_H
#define IMPROVEMENT_H

#include "tile.h"
#include "board.h"
#include "hexLoc.h"

class Improvement {
public:
	Improvement();
	Improvement(cube_t coords, int direction);

	void buildCity();
	coords_t getCenter(int tileSize);
	cube_t getHexCoords(int tileIndex) { return tileArray[tileIndex]; }
	HexLoc getHexLoc() { return hexLoc; }

	bool checkCorner(cube_t tile, int corner);
	bool checkLocation(cube_t tile, int corner);
		
private:
	bool typeCity; //false for settlement, true for city
	cube_t tileArray[3];			//any Improvement will be at the intersection of 3 tiles, store positions of these tiles
	int tileCorner;					//for the first tile, a corner is specified where to keep track of its location 0 is upper coner, increasing clockwise
	int blockedCorners[3];			//blocked corners correspond to the tileArray (i.e. blocked corner 0 is with respect to tile 0, while blocked corner 1 is on tile 1)

	HexLoc hexLoc;
};

#endif