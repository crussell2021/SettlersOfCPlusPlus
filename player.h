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
	void setNumberOfSheep(int number) { sheepCards = number; }
	int getNumberOfRock() { return rockCards; }
	void setNumberOfRock(int number) { rockCards = number; }
	int getNumberOfBricks() { return brickCards; }
	void setNumberOfBricks(int number) { brickCards = number; }
	int getNumberOfWood() { return woodCards; }
	void setNumberOfWood(int number) { woodCards = number; }
	int getNumberOfWheat() { return wheatCards; }
	void setNumberOfWheat(int number) { wheatCards = number; }
	int getNumberOfDevCards() { return devCards; }
	void setNumberOfDevCards(int dev) { devCards = dev; }

	int getNumberOfRoads() { return numberOfRoads; }
	int getNumberOfSettlements() { return numberOfSettlements; }
	int getNumberOfCities() { return numberOfCities; }

	Road getRoad(int index) { return roadArray[index]; };
	Improvement getSettlement(int index);
	Improvement getCity(int index) { return cityArray[index]; }

	void makeSettlement(cube_t tile, int corner);
	void makeCity(cube_t tile, int corner);
	void makeRoad(cube_t tile, int corner1, int corner2);
	void makeRoad(Road road);

	void gainResource(int type);

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