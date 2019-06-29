#ifndef PLAYER_H
#define PLAYER_H
#include "improvement.h"
#include "road.h"

enum playerColor{red,blue,green,yellow,orange,white};

class Player {
public:
	Player();
	Player(int color);

	int getColor() { return color; }
	int getNumberOfSheep() { return sheepCards; }
	int getNumberOfRock() { return rockCards; }
	int getNumberOfBricks() { return brickCards; }
	int getNumberOfWood() { return woodCards; }
	int getNumberOfWheat() { return wheatCards; }
	int getNumberOfDevCards() { return devCards; }

	int getNumberOfRoads() { return numberOfRoads; }
	int getNumberOfSettlements() { return numberOfSettlements; }
	int getNumberOfCities() { return numberOfCities; }

	Road getRoad(int index) { return roadArray[index]; }
	Improvement getSettlement(int index) { return settlementArray[index]; }
	Improvement getCity(int index) { return cityArray[index]; }

	void makeSettlement(cube_t tile, int corner);
	void makeRoad(cube_t tile, int corner1, int corner2);

	void gainResource(tileType type);

private:
	int victoryPoints;
	playerColor color;

	int sheepCards;
	int rockCards;
	int brickCards;
	int woodCards;
	int wheatCards;
	int devCards;

	int numberOfRoads;
	int numberOfSettlements;
	int numberOfCities;

	Improvement settlementArray[5];
	Improvement cityArray[4];
	Road roadArray[15];


};

#endif