#include "Tile.h"
#include <math.h>

Tile::Tile() {
	x = 0;
	y = 0;
	z = 0;
	number = 0;
	resource = sand;
}

Tile::Tile(int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
	number = 0;
	resource = sand;
}

Tile::Tile(cube_t cube) {
	x = cube.x;
	y = cube.y;
	z = cube.z;
	number = 0;
	resource = sand;
}

cube_t Tile::getHexCoords() {
	cube_t hex;
	hex.x = x;
	hex.y = y;
	hex.z = z;
	return hex;
}

cube_t Tile::getNeighbor(int direction) {
	cube_t hex = getHexCoords();
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
cube_t Tile::getNeighbor(cube_t hex, int direction) {
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

void Tile::setHexCoordinates(cube_t cube) {
	x = cube.x;
	y = cube.y;
	z = cube.z;
}

coords_t Tile::getTileCenter(int tileSize) {
	coords_t coords;
	coords.x = (int)(tileSize * ( x + (z/2.0 ) ) );
	coords.y = (int)(tileSize * ((3.0 / 4.0) * z) );
	return coords;
}

coords_t Tile::getTileCenter(cube_t tile, int tileSize) {
	coords_t coords;
	coords.x = (int)(tileSize * (tile.x + (tile.z / 2.0)));
	coords.y = (int)(tileSize * ((3.0 / 4.0) * tile.z));
	return coords;
}


coords_t Tile::getPosOffset(int position, int tileSize) {
	coords_t coords = {0,0};
	switch (position) {
	case 0: coords.y = -tileSize / 2; break;
	case 1: coords.y = -tileSize / 4; coords.x = tileSize / 2;
	case 2: coords.y = tileSize / 4; coords.x = tileSize / 2;
	case 3: coords.y = tileSize / 2; break;
	case 4: coords.y = tileSize / 4; coords.x = -tileSize / 2;
	case 5: coords.y = -tileSize / 4; coords.x = -tileSize / 2;
	}
	return coords;
}