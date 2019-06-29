#include "road.h"
#include <iostream>

Road::Road() {
	cube_t newTile = { 0,0,0 };
	tile = newTile;
	corner[0] = 0;
	corner[1] = 0;
	direction = 0;
	location = 0;
	locationCorners[0] = HexLoc::combine(tile, corner[0]);
	locationCorners[1] = HexLoc::combine(tile, corner[1]);
}

Road::Road(cube_t tile, int corner1, int corner2) {
	this->tile = tile;
	if (corner2 == corner1) {		//cannot create a road with the same corners
		corner2++;
		if (corner2 == 6) {
			corner2 = 0;
		}
	}
	corner[0] = corner1;
	corner[1] = corner2;	
	direction = 0; 
	location = 0;
	//choose direction, 0 is straight up and down, 1 points up, 2 points down (see sprite sheet for images)
	switch (corner1) {
		case 0: if (corner2 == 5) { direction = 1; location = 0; } if (corner2 == 1) { direction = 2; location = 1; } break;
		case 1: if (corner2 == 0) { direction = 2; location = 1; } if (corner2 == 2) { direction = 0; location = 2; } break;
		case 2: if (corner2 == 1) { direction = 0; location = 2; } if (corner2 == 3) { direction = 1; location = 3; } break;
		case 3: if (corner2 == 2) { direction = 1; location = 3; } if (corner2 == 4) { direction = 2; location = 4; } break;
		case 4: if (corner2 == 3) { direction = 2; location = 4; } if (corner2 == 5) { direction = 0; location = 5; } break;
		case 5: if (corner2 == 4) { direction = 0; location = 5; } if (corner2 == 0) { direction = 1; location = 0; } break;
		default: corner[0] = 0; corner[1] = 0;	//bad case
	}
	locationCorners[0] = HexLoc::combine(tile, corner[0]);
	locationCorners[1] = HexLoc::combine(tile, corner[1]);
}

bool Road::containsCorner(HexLoc location) {
	if (location == locationCorners[0] || location == locationCorners[1]) {
		return true; //passed check
	}
	return false; //failed check
}

//depricated, move to HexLoc system
bool Road::checkCorner(cube_t tile, int corner) {
	if (tile.x != this->tile.x || tile.y != this->tile.y || tile.z != this->tile.z || (corner != this->corner[0] && corner != this->corner[1])) {
		return false;
	}
	return true;
}

coords_t Road::getImageLocation(int tileSize) {
	   
	coords_t coords = getTile().getTileCenter(tileSize);		//get center coords of tile
		
	switch (location) {											//then based on location, move to top left of image
	case 0: coords.x -= tileSize / 4; coords.y -= 3 * tileSize / 8; break;
	case 1: coords.x += tileSize / 4; coords.y -= 3 * tileSize / 8; break;
	case 2: coords.x += tileSize / 2; coords.y += 0; break;
	case 3: coords.x += tileSize / 4; coords.y += 3 * tileSize / 8; break;
	case 4: coords.x -= tileSize / 4; coords.y += 3 * tileSize / 8; break;
	case 5: coords.x -= tileSize / 2; coords.y += 0; break;
	}
	return coords;
}
