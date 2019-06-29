#include "board.h"

CatanBoard::CatanBoard(int size) {
	this->size = size;
	numberOfTiles = 0;
	maxNumberOfTiles = 1;											//number of tiles in a game is calculated in this loop
	for (int i = 1; i < size; i++) {
		maxNumberOfTiles += (6 * i);
	}
	tiles = new Tile[maxNumberOfTiles];
	tiles[numberOfTiles++] = Tile();								//create first tile in the array using default constructor (0,0,0)

	createTileSpiral(size);											//create the rest of map through spiral algorithm
	loadTileTypes();
	randomizeTileType();
	loadTileNumbers(3, 11);
	randomizeTileNumbers();
}

void CatanBoard::newTile(cube_t coords) {			//creates next tile in array, only if theres room in array
	if (numberOfTiles < maxNumberOfTiles) {
		tiles[numberOfTiles++] = Tile(coords);
	}
}

void CatanBoard::createTileRing(int radius) {
	Tile tile;								//create tile at center (0,0,0) and coords variable to keep track of position
	cube_t coords;						
	for (int i = 0; i < radius; i++) {		//move tile out from center a dsitance of radius ((-1,+0,+1) * radius)
		coords = tile.getNeighbor(4);		//set coords to this pos
		tile.setHexCoordinates(coords);		//set tile to pos				this step could be simplified by overloading '=' operator
	}
	for (int i = 0; i < 6; i++) {			//cyles through directions
		for (int j = 0; j < radius; j++) {	//the radius of the ring is also the number of time you need to go in that direction for
			newTile(coords);				//set next tile in array to this position
			coords = tile.getNeighbor(i);	//get next tile coords
			tile.setHexCoordinates(coords);	//update tile to next position
		}
	}
}
void CatanBoard::createTileSpiral(int radius) {
	Tile tile;								//create tile at center
	for (int i = 1; i < radius; i++) {		//runs createTileRing for each radius
		createTileRing(i);
	}
}

coords_t CatanBoard::getTileCenter(int index, int tileSize) {		//returns center coordinated of tile, used for printing tiles to screen
	return tiles[index].getTileCenter(tileSize);
}

coords_t CatanBoard::getCornerCoords(int index, int corner, int tileSize) {		//returns center coordinated of tile, used for printing tiles to screen
	coords_t coords = tiles[index].getTileCenter(tileSize);
	switch (corner) {
		case 0: coords.x += 0; coords.y -= tileSize / 2; break;
		case 1: coords.x += tileSize / 2; coords.y -= tileSize / 4; break;
		case 2: coords.x += tileSize / 2; coords.y += tileSize / 4; break;
		case 3: coords.x -= 0; coords.y += tileSize / 2; break;
		case 4: coords.x -= tileSize / 2; coords.y += tileSize / 4; break;
		case 5: coords.x -= tileSize / 2; coords.y -= tileSize / 4; break;
	}
	
	return coords;
}

coords_t CatanBoard::getCornerCoords(cube_t tile, int corner, int tileSize) {		//returns center coordinated of tile, used for printing tiles to screen
	coords_t coords = Tile::getTileCenter(tile, tileSize);
	switch (corner) {
	case 0: coords.x += 0; coords.y -= tileSize / 2; break;
	case 1: coords.x += tileSize / 2; coords.y -= tileSize / 4; break;
	case 2: coords.x += tileSize / 2; coords.y += tileSize / 4; break;
	case 3: coords.x -= 0; coords.y += tileSize / 2; break;
	case 4: coords.x -= tileSize / 2; coords.y += tileSize / 4; break;
	case 5: coords.x -= tileSize / 2; coords.y -= tileSize / 4; break;
	}

	return coords;
}

coords_t CatanBoard::getBorderCoords(int index, int tileSize) {
	coords_t coords;
	switch (index) {
		case 0: coords.x = -1.5 * tileSize; coords.y = -2.25 * tileSize; break;		//top piece	+
		case 1: coords.x = -1.5 * tileSize; coords.y = 1.75 * tileSize; break;		//bottom piece	+
		case 2: coords.x = -2.25 * tileSize; coords.y = -2.75 * tileSize; break;	//top left
		case 3: coords.x = -3 * tileSize; coords.y = 0; break;						//bottom left	+
		case 4: coords.x = 1.25 * tileSize; coords.y = -2.25 * tileSize; break;		//top right	+
		case 5: coords.x = 1.5 * tileSize; coords.y = 0; break;						//bottom right
		default: coords.x = 0; coords.y = 0;										//bad case
	}
	return coords;
}

void CatanBoard::randomizeTileType() {
	tileType temp;
	srand(time(NULL));
	int m, n;
	for (int i = 0; i < 50; i++) {
		m = (rand() % (numberOfTiles - 1)) + 1;			//choose random numbers from 1 to numberOfTiles
		n = (rand() % (numberOfTiles - 1)) + 1;
		temp = tiles[n].getType();
		tiles[n].setType(tiles[m].getType());
		tiles[m].setType(temp);
	}
}

void CatanBoard::loadTileTypes() {
	for (int i = 1; i < numberOfTiles; i++) {
		tiles[i].setType(tileType( (i % 5) + 1));
	}
}

void CatanBoard::randomizeTileNumbers() {
	int temp;
	srand(time(NULL));
	int m, n;
	for (int i = 0; i < 50; i++) {
		m = (rand() % (numberOfTiles - 1)) + 1;			//choose random numbers from 1 to numberOfTiles
		n = (rand() % (numberOfTiles - 1)) + 1;
		temp = tiles[n].getNumber();					//swap values
		tiles[n].setNumber(tiles[m].getNumber());
		tiles[m].setNumber(temp);
	}
}

void CatanBoard::loadTileNumbers(int extra1, int extra2) {
	tiles[1].setNumber(extra1);							//generate numbers 2 thourgh 12, with no 7, only one 2 and one 12, the rest have two
	tiles[numberOfTiles - 1].setNumber(extra2);			//some house rules replace the 2 and 12 with other numbers, so this is an option
	int number;
	for (int i = 2; i < numberOfTiles - 1; i++) {		
		number = (i % 8) + 3;						//generates numbers 3 through 10
		if (number == 7) {							//replace any 7s with 11s
			number = 11;
		}
		tiles[i].setNumber(number);		
	}
}

int CatanBoard::getTileByCoords(cube_t tile) {
	cube_t currentTile;
	for (int i = 0; i < numberOfTiles; i++) {
		currentTile = tiles[i].getHexCoords();
		if (currentTile.x == tile.x && currentTile.y == tile.y && currentTile.z == tile.z) {
			return i;
		}
	}
	return -1;	//couldnt find tile with parameters coords
}