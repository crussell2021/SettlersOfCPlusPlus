#include "improvement.h"

Improvement::Improvement() {				//default constructo will place a settlement at the 0 corner of the center tile
	typeCity = false;
	hexLoc = HexLoc();
	tileArray[0] = Tile().getHexCoords();		//default tile constructor
	tileCorner = 0;			//corner 0 (top)
	//use ^^ to determine other two tiles
	int dir1 = tileCorner, dir2 = tileCorner + 1;	//the directions from the initial tile that maps to the other two tile are the same value as the corner, adn the corner plus 1
	if (dir1 == 6) {										//check if the dir1 is outside the bounds, reset it to 0
		dir1 = 0;
	} else if (dir2 == 6) {									//check if the dir2 is outside the bounds, reset it to 0
		dir2 = 0;
	}
	tileArray[1] = Tile::getNeighbor(tileArray[0], dir1);
	tileArray[2] = Tile::getNeighbor(tileArray[0], dir2);
	blockedCorners[0] = tileCorner + 1;
	if (blockedCorners[0] == 6) {
		blockedCorners[0] = 0;
	}

	blockedCorners[1] = tileCorner + 1;
	if (blockedCorners[0] == 6) {
		blockedCorners[0] = 0;
	}

	blockedCorners[2] = tileCorner - 1;
	if (blockedCorners[0] == -1) {
		blockedCorners[0] = 5;
	}
}

Improvement::Improvement(cube_t coords, int corner) {				//coinstructor from a tile's hex coords and the corner the Improvement is on
	hexLoc = HexLoc::combine(coords, corner);
	typeCity = false;
	tileArray[0] = coords;									//inital tile
	tileCorner = corner;									//corner of initial tile
	//use ^^ to determine other two tiles
	int dir1 = tileCorner, dir2 = tileCorner + 1;			//the directions from the initial tile that maps to the other two tile 
	if (dir1 == 6) {										//check if the dir1 is outside the bounds, reset it to 0
		dir1 = 0;
	}
	else if (dir2 == 6) {									//check if the dir2 is outside the bounds, reset it to 0
		dir2 = 0;
	}
	tileArray[1] = Tile::getNeighbor(tileArray[0], dir1);	//find the adjacent two tiles
	tileArray[2] = Tile::getNeighbor(tileArray[0], dir2);

	blockedCorners[0] = tileCorner + 1;
	if (blockedCorners[0] == 6) {
		blockedCorners[0] = 0;
	}

	blockedCorners[1] = tileCorner + 1;
	if (blockedCorners[1] == 6) {
		blockedCorners[1] = 0;
	}

	blockedCorners[2] = tileCorner - 1;
	if (blockedCorners[2] == -1) {
		blockedCorners[2] = 5;
	}
}

void Improvement::buildCity() {
	typeCity = true;
}
coords_t Improvement::getCenter(int tileSize) {
	return CatanBoard::getCornerCoords(tileArray[0], tileCorner, tileSize);
}

bool Improvement::checkCorner(cube_t tile, int corner) {
	for (int i = 0; i < 3; i++) {
		if ((blockedCorners[i] == corner) && (tileArray[i].x == tile.x) && (tileArray[i].y == tile.y) && (tileArray[i].z == tile.z)) {		//if tile and corner exactly match
			return false;		//this tile is blocked
		}
	}
	return true;				//all corners have been checked, corner does not conflict with this improvement
}

bool Improvement::checkLocation(cube_t tile, int corner) {
	if (tileArray[0].x == tile.x && tileArray[0].y == tile.y && tileArray[0].z == tile.z && corner == tileCorner) {
		return true;//the parameters match exactly
	}
	return false; //the parameters were not a match
}