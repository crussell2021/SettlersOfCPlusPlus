#ifndef HEXLOC_H
#define HEXLOC_H

#include "tile.h"

class HexLoc {
public:
	HexLoc();
	HexLoc(cube_t tile);
	HexLoc(cube_t tile, int pos);

	cube_t getHexCoords() { return hexCoords; }
	int getPos() { return cornerPos; }

	static HexLoc combine(cube_t tile, int pos);

	static bool compareEqual(HexLoc, HexLoc);

	friend bool operator==(const HexLoc& loc1, const HexLoc& loc2);

private:
	cube_t hexCoords;
	int cornerPos;

};

bool operator==(const HexLoc& loc1, const HexLoc& loc2);

#endif