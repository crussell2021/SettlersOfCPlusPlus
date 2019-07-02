#ifndef HEXLOC_H
#define HEXLOC_H

//a convinient way to store hex coorinates, see https://www.redblobgames.com/grids/hexagons/ for reference
struct cube_t {
	int x;
	int y;
	int z;
};

#ifndef COORDS_T
#define COORDS_T
struct coords_t {
	int x;
	int y;

	coords_t(int x = 0, int y = 0) : x(x), y(y) {}

	coords_t& operator=(const coords_t& coords) {
		x = coords.x;
		y = coords.y;
		return *this;
	}

	coords_t operator+(const coords_t& coords) const {
		return coords_t(coords.x + x, coords.y + y);
	}

	bool operator==(const coords_t & coords) {
		return (x == coords.x && y == coords.y);
	}
};
#endif

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

	coords_t getLocationCenter(int tileSize);

	static cube_t getNeighbor(cube_t coords, int direction);
	static coords_t getTileCenter(cube_t tile, int tileSize = 64);		//numbers divisable by 8 will work best in calcualtion, because coords are stored as ints, not floats
	static coords_t getPosOffset(int position, int tileSize = 64);
	static coords_t getLocationCenter(HexLoc, int tileSize = 64);

private:
	cube_t hexCoords;
	int cornerPos;
	bool valid;	//tracks if a hexLoc was created using a real constructor or is just a generic one created by default constructor
};

bool operator==(const HexLoc& loc1, const HexLoc& loc2);

#endif