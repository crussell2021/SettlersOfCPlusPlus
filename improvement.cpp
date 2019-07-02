#include "improvement.h"

Improvement::Improvement() {
	typeCity = false;
	for (int i = 0; i < 3; i++) {
		tileArray[i].x = 0;
		tileArray[i].y = 0;
		tileArray[i].z = 0;
		adjacentCorners[i] = HexLoc();
	}
	hexLoc = HexLoc();
}

Improvement::Improvement(cube_t coords, int corner, bool city) {				//coinstructor from a tile's hex coords and the corner the Improvement is on
	int cornerArray[3];
	
	typeCity = city;

	hexLoc = HexLoc::combine(coords, corner);

	tileArray[0] = coords;
	tileArray[1] = HexLoc::getNeighbor(coords, corner);
	tileArray[2] = HexLoc::getNeighbor(coords, corner + 1);

	cornerArray[0] = corner + 1;
	if (cornerArray[0] == 6) {
		cornerArray[0] = 0;
	}
	cornerArray[1] = cornerArray[0] + 2;
	if (cornerArray[1] > 5) {
		cornerArray[1] -= 6;
	}
	cornerArray[2] = cornerArray[1] + 2;
	if (cornerArray[2] > 5) {
		cornerArray[2] -= 6;
	}

	for (int i = 0; i < 3; i++) {
		adjacentCorners[i] = HexLoc::combine(tileArray[i], cornerArray[i]);
	}

}

Improvement::Improvement(HexLoc location, bool city) {				//coinstructor from a tile's hex coords and the corner the Improvement is on
	int cornerArray[3];

	typeCity = city;

	hexLoc = location;

	tileArray[0] = location.getHexCoords();
	tileArray[1] = HexLoc::getNeighbor(tileArray[0], location.getPos());
	tileArray[2] = HexLoc::getNeighbor(tileArray[0], location.getPos() + 1);

	cornerArray[0] = location.getPos() + 1;
	if (cornerArray[0] == 6) {
		cornerArray[0] = 0;
	}
	cornerArray[1] = cornerArray[0] + 2;
	if (cornerArray[1] > 5) {
		cornerArray[1] -= 6;
	}
	cornerArray[2] = cornerArray[1] + 2;
	if (cornerArray[2] > 5) {
		cornerArray[2] -= 6;
	}

	for (int i = 0; i < 3; i++) {
		adjacentCorners[i] = HexLoc::combine(tileArray[i], cornerArray[i]);
	}

}

void Improvement::buildCity() {
	typeCity = true;
}

coords_t Improvement::getCenter(int tileSize) {
	return HexLoc::getLocationCenter(hexLoc, tileSize);
}

bool Improvement::isCornerOpen(cube_t tile, int corner) {
	HexLoc location(tile, corner);
	for (int i = 0; i < 3; i++) {
		if (adjacentCorners[i] == location) {		//if tile and corner exactly match
			return false;		//this tile is blocked
		}
	}
	return true;				//all corners have been checked, corner does not conflict with this improvement
}

bool Improvement::isLocationOpen(HexLoc location) {
	for (int i = 0; i < 3; i++) {
		if (adjacentCorners[i] == location) {		//if tile and corner exactly match
			return false;		//this tile is blocked
		}
	}
	return true;				//all corners have been checked, corner does not conflict with this improvement
}