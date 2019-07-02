#include "hexLoc.h"

HexLoc::HexLoc() {
	hexCoords = { 0,0,0 };
	cornerPos = 0;
	valid = false;
}

HexLoc::HexLoc(cube_t tile) {
	hexCoords = tile;
	cornerPos = 0;
	valid = true;
}

HexLoc::HexLoc(cube_t tile, int pos) {
	hexCoords = tile;
	cornerPos = pos;
	valid = true;
}

bool HexLoc::compareEqual(HexLoc loc1, HexLoc loc2) {
	coords_t pos1 = getTileCenter(loc1.getHexCoords()) + getPosOffset(loc1.getPos());		//use two dimensional coordinates to compare HexLoc
	coords_t pos2 = getTileCenter(loc2.getHexCoords()) + getPosOffset(loc2.getPos());		//this makes sure that even if a location is stored under different tiles, an accurate answer is given
	return (pos1 == pos2);
}

HexLoc HexLoc::combine(cube_t tile, int pos) {
	return HexLoc(tile, pos);
}

bool operator== (const HexLoc& loc1, const HexLoc& loc2) {
	return HexLoc::compareEqual(loc1, loc2);
}

cube_t HexLoc::getNeighbor(cube_t hex, int direction) {
	if (direction > 5) {
		direction -= 6;
	}
	if (direction < 5) {
		direction += 6;
	}
	switch (direction) {
	case 0: hex.x += 0; hex.y += 1; hex.z += -1; break;
	case 1: hex.x += 1; hex.y += 0; hex.z += -1; break;
	case 2: hex.x += 1; hex.y += -1; hex.z += 0; break;
	case 3: hex.x += 0; hex.y += -1; hex.z += 1; break;
	case 4: hex.x += -1; hex.y += 0; hex.z += 1; break;
	case 5: hex.x += -1; hex.y += 1; hex.z += 0; break;
	default: hex.x += 0; hex.y += 0; hex.z += 0;	//bad case
	}
	return hex;
}

coords_t HexLoc::getTileCenter(cube_t tile, int tileSize) {
	coords_t coords;
	coords.x = (int)(tileSize * (tile.x + (tile.z / 2.0)));
	coords.y = (int)(tileSize * ((3.0 / 4.0) * tile.z));
	return coords;
}


coords_t HexLoc::getPosOffset(int position, int tileSize) {
	coords_t coords = { 0,0 };
	switch (position) {
		case 0: coords.y = -tileSize / 2; break;
		case 1: coords.y = -tileSize / 4; coords.x = tileSize / 2; break;
		case 2: coords.y = tileSize / 4; coords.x = tileSize / 2; break;
		case 3: coords.y = tileSize / 2; break;
		case 4: coords.y = tileSize / 4; coords.x = -tileSize / 2; break;
		case 5: coords.y = -tileSize / 4; coords.x = -tileSize / 2; break;
	}
	return coords;
}

coords_t HexLoc::getLocationCenter(int tileSize) {
	coords_t coords;
	coords = getTileCenter(hexCoords, tileSize) + getPosOffset(cornerPos, tileSize);
	return coords;
}

coords_t HexLoc::getLocationCenter(HexLoc location, int tileSize) {
	coords_t coords;
	coords = getTileCenter(location.getHexCoords(), tileSize) + getPosOffset(location.getPos(), tileSize);
	return coords;
}