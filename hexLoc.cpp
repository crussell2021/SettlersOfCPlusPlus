#include "hexLoc.h"

HexLoc::HexLoc() {
	hexCoords = { 0,0,0 };
	cornerPos = 0;
}

HexLoc::HexLoc(cube_t tile) {
	hexCoords = tile;
	cornerPos = 0;
}

HexLoc::HexLoc(cube_t tile, int pos) {
	hexCoords = tile;
	cornerPos = pos;
}

bool HexLoc::compareEqual(HexLoc loc1, HexLoc loc2) {
	coords_t pos1 = Tile::getTileCenter(loc1.getHexCoords()) + Tile::getPosOffset(loc1.getPos());		//use two dimensional coordinates to compare HexLoc
	coords_t pos2 = Tile::getTileCenter(loc2.getHexCoords()) + Tile::getPosOffset(loc2.getPos());		//this makes sure that even is a location is stored under different tiles, an accurate answer is given
	return (pos1 == pos2);
}

HexLoc HexLoc::combine(cube_t tile, int pos) {
	return HexLoc(tile, pos);
}

bool operator== (const HexLoc& loc1, const HexLoc& loc2) {
	return HexLoc::compareEqual(loc1, loc2);
}