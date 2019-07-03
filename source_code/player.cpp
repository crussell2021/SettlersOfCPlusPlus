#include "player.h"

Player::Player() {
	color = orange;
	sheepCards = 0;
	rockCards = 0;
	brickCards = 0;
	woodCards = 0;
	wheatCards = 0;
	devCards = 0;

	victoryPoints = 0;
	numberOfRoads = 0;
	numberOfSettlements = 0;
	numberOfCities = 0;

}

Player::Player(int color) {
	this->color = playerColor(color);
	sheepCards = 0;
	rockCards = 0;
	brickCards = 0;
	woodCards = 0;
	wheatCards = 0;
	devCards = 0;

	victoryPoints = 0;
	numberOfRoads = 0;
	numberOfSettlements = 0;
	numberOfCities = 0;

}

void Player::makeSettlement(cube_t tile, int corner) {
	settlementArray[numberOfSettlements++] = Improvement(tile, corner);
}

void Player::makeCity(cube_t tile, int corner) {
	cityArray[numberOfCities++] = Improvement(tile, corner, true);
}

void Player::makeRoad(cube_t tile, int corner1, int corner2) {
	roadArray[numberOfRoads++] = Road(tile, corner1, corner2);
}

void Player::makeRoad(Road road) {
	roadArray[numberOfRoads++] = road;
}

void Player::gainResource(int type) {
	switch (type) {
	case 1: woodCards++; break;
	case 2: brickCards++; break;
	case 3: sheepCards++; break;
	case 4: wheatCards++; break;
	case 5: rockCards++; break;
	}
}

Improvement Player::getSettlement(int index) {
	return settlementArray[index];
}