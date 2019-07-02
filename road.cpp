#include "road.h"
#include <iostream>

Road::Road() {
	cube_t tile = { 0,0,0 };
	corner[0] = 0;
	corner[1] = 0;
	orientation = 0;
	location = 0;
	locationCorners[0] = HexLoc::combine(tile, corner[0]);
	locationCorners[1] = HexLoc::combine(tile, corner[1]);
}

Road::Road(cube_t tile, int corner1, int corner2) {
	if (corner2 == corner1) {		//cannot create a road with the same corners
		corner2++;
		if (corner2 == 6) {
			corner2 = 0;
		}
	}
	if (corner1 == 6) {
		corner1 = 0;
	}
	if (corner2 == 6) {
		corner2 = 0;
	}
	corner[0] = corner1;
	corner[1] = corner2;	
	orientation = 0; 
	location = 0;
	//choose orientation, 0 is straight up and down, 1 points up, 2 points down (see sprite sheet for images)
	switch (corner1) {
		case 0: if (corner2 == 5) { orientation = 1; location = 0; } if (corner2 == 1) { orientation = 2; location = 1; } break;
		case 1: if (corner2 == 0) { orientation = 2; location = 1; } if (corner2 == 2) { orientation = 0; location = 2; } break;
		case 2: if (corner2 == 1) { orientation = 0; location = 2; } if (corner2 == 3) { orientation = 1; location = 3; } break;
		case 3: if (corner2 == 2) { orientation = 1; location = 3; } if (corner2 == 4) { orientation = 2; location = 4; } break;
		case 4: if (corner2 == 3) { orientation = 2; location = 4; } if (corner2 == 5) { orientation = 0; location = 5; } break;
		case 5: if (corner2 == 4) { orientation = 0; location = 5; } if (corner2 == 0) { orientation = 1; location = 0; } break;
		default: corner[0] = 0; corner[1] = 0;	//bad case
	}
	locationCorners[0] = HexLoc::combine(tile, corner[0]);
	locationCorners[1] = HexLoc::combine(tile, corner[1]);
}

Road::Road(HexLoc loc1, HexLoc loc2) {
	locationCorners[0] = loc1;
	locationCorners[1] = loc2;

	int corner1 = loc1.getPos();
	int corner2 = loc2.getPos();

	corner[0] = corner1;
	corner[1] = corner2;
	orientation = 0;
	location = 0;
	//choose orientation, 0 is straight up and down, 1 points up, 2 points down (see sprite sheet for images)
	switch (corner1) {
	case 0: if (corner2 == 5) { orientation = 1; location = 0; } if (corner2 == 1) { orientation = 2; location = 1; } break;
	case 1: if (corner2 == 0) { orientation = 2; location = 1; } if (corner2 == 2) { orientation = 0; location = 2; } break;
	case 2: if (corner2 == 1) { orientation = 0; location = 2; } if (corner2 == 3) { orientation = 1; location = 3; } break;
	case 3: if (corner2 == 2) { orientation = 1; location = 3; } if (corner2 == 4) { orientation = 2; location = 4; } break;
	case 4: if (corner2 == 3) { orientation = 2; location = 4; } if (corner2 == 5) { orientation = 0; location = 5; } break;
	case 5: if (corner2 == 4) { orientation = 0; location = 5; } if (corner2 == 0) { orientation = 1; location = 0; } break;
	default: corner[0] = 0; corner[1] = 0;	//bad case
	}

}

bool Road::containsCorner(HexLoc location) {
	if (location == locationCorners[0] || location == locationCorners[1]) {
		return true; //passed check
	}
	return false; //failed check
}

coords_t Road::getImageLocation(int tileSize) {		//image origin should be top left corner, so return the lowest x and y to get origin
	coords_t coords;
	coords_t coords1 = locationCorners[0].getLocationCenter(tileSize);
	coords_t coords2 = locationCorners[1].getLocationCenter(tileSize);
	if (coords1.x < coords2.x) {
		coords.x = coords1.x;
	} else {
		coords.x = coords2.x;
	}

	if (coords1.y < coords2.y) {
		coords.y = coords1.y;
	}
	else {
		coords.y = coords2.y;
	}

	return coords;
}
