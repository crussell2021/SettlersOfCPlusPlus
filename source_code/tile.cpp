#include "Tile.h"
#include <math.h>

Tile::Tile() {
	cube_t cube = { 0, 0, 0 };
	hexCoords = cube;
	number = 0;
	resource = 0;
}

Tile::Tile(cube_t cube) {
	hexCoords = cube;
	number = 0;
	resource = 0;
}

void Tile::setHexCoords(cube_t tile) {
	hexCoords = tile;
}

cube_t Tile::getHexCoords() {
	return hexCoords;
}

cube_t Tile::getNeighbor(int direction) {
	cube_t hex = getHexCoords();
	while (direction > 5) {
		direction = direction - 6;
	}
	while (direction < 0) {
		direction = direction + 6;
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

coords_t Tile::getTileCenter(int tileSize) {
	coords_t coords;
	coords.x = (int)(tileSize * ( hexCoords.x + (hexCoords.z/2.0 ) ) );
	coords.y = (int)(tileSize * ((3.0 / 4.0) * hexCoords.z) );
	return coords;
}