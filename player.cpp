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

void Player::makeRoad(cube_t tile, int corner1, int corner2) {
	roadArray[numberOfRoads++] = Road(tile, corner1, corner2);
}

void Player::gainResource(tileType type) {
	switch (type) {
	case sheep: sheepCards++; break;
	case rock: rockCards++; break;
	case brick: brickCards++; break;
	case wood: woodCards++; break;
	case wheat: wheatCards++; break;
	}
}