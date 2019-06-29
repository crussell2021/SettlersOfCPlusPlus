// SettlersOfC++ main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include "display.h"
#include "gameControl.h"

void printPlayerPanels(Display screen, GameController game);
void printBoard(Display screen, CatanBoard map);
void printBuildings(Display screen, GameController game);

bool buildRoad(Display screen, CatanBoard map, GameController& game, Player& player, bool initialPlace = false);
bool buildSettlement(Display screen, CatanBoard map, GameController& game, Player& player, bool initialPlace = false);

bool getImprovementLocation(Display screen, CatanBoard map, GameController game, Player player, int& tile, int& corner);
bool getRoadLocation(Display screen, CatanBoard map, GameController game, Player player, int& tile, int& corner1, int& corner2);

void refreshScreen(Display screen, CatanBoard map, GameController game);

int main(int argc, char* argv[]) {
	int numberOfPlayers;
	std::cout << "How many players? ";
	std::cin >> numberOfPlayers;
	
	Display display;
	display.loadSpritePage("128hexsetBuildingFrame2.png");
	GameController game;
	game.addPlayers(numberOfPlayers);
	
	refreshScreen(display, game.map, game);

	std::cout << "Set up phase: place initial tiles" << std::endl;
	
	for (int i = 0; i < game.getNumberOfPlayers(); i++) {
		std::cout << std::endl;
		if (!buildSettlement(display, game.map, game, game.getPlayerPointer(i), true)) {
			return 0;
		}
		else {
			refreshScreen(display, game.map, game);
		}

		if (!buildRoad(display, game.map, game, game.getPlayerPointer(i), true)) {
			return 0;
		}
		else {
			refreshScreen(display, game.map, game);
		}
	}
	for (int i = game.getNumberOfPlayers(); i > 0; i--) {
		std::cout << std::endl;
		if (!buildSettlement(display, game.map, game, game.getPlayerPointer(i - 1), true)) {
			return 0;
		}
		else {
			refreshScreen(display, game.map, game);
		}

		if (!buildRoad(display, game.map, game, game.getPlayerPointer(i - 1), true)) {
			return 0;
		}
		else {
			refreshScreen(display, game.map, game);
		}
	}
	game.initialResources();
		
	bool gameRunning = true;
	while (gameRunning) {
		if (display.checkUpdate()) {
			refreshScreen(display, game.map, game);
			display.clearUpdate();
		}
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameRunning = false;
			}
		}
	}
	display.cleanup();
	return 0;
}

void printPlayerPanels(Display screen, GameController game) {
	int width = 250, height = 125;
	int panelX, panelY;
	for (int i = 0; i < game.getNumberOfPlayers(); i++) {
		panelX = (i % 2) * (screen.getScreenWidth() - 250);
		if (i < 2) {
			panelY = 0;
		}
		else {
			panelY = screen.getScreenHeight() - 125;
		}
		screen.placeSolidRectangle(52, 82, 128, panelX, panelY, width, height);
		screen.printText("Player " + std::to_string(i + 1), panelX + 5, panelY + 5);
		screen.printText("Wood: " + std::to_string(game.getPlayer(i).getNumberOfWood()) + "  Bricks: " + std::to_string(game.getPlayer(i).getNumberOfBricks()), panelX + 10, panelY + 32);
		screen.printText("Sheep: " + std::to_string(game.getPlayer(i).getNumberOfSheep()) + "  Wheat: " + std::to_string(game.getPlayer(i).getNumberOfWheat()), panelX + 10, panelY + 64);
		screen.printText("Rock: " + std::to_string(game.getPlayer(i).getNumberOfSheep()) + "  Development Cards: " + std::to_string(game.getPlayer(i).getNumberOfDevCards()), panelX + 10, panelY + 96);
	}
}


void printBoard(Display screen, CatanBoard map) {
	int tiles = map.getNumberOfTiles();
	coords_t imageCoords;
	coords_t centerCoords = screen.center();
	for (int i = 0; i < tiles; i++) {
		imageCoords = map.getTileCenter(i, 128);
		screen.placeTexture(128 * map.getTileType(i), 0, centerCoords.x + imageCoords.x - 64, centerCoords.y + imageCoords.y - 64);							//place hexes
		screen.placeTexture(32 * (map.getTileNumber(i) - 1), 128, centerCoords.x + imageCoords.x - 16, centerCoords.y + imageCoords.y - 16, 32, 32);			//place numbers
	}
}


void refreshScreen(Display screen, CatanBoard map, GameController game) {
	screen.clearScreen();

	printPlayerPanels(screen, game);

	printBoard(screen, map);

	printBuildings(screen, game);

	//printKnight();

	screen.update();

	screen.clearUpdate();

}


bool buildSettlement(Display screen, CatanBoard map, GameController &game, Player &player, bool initialPlace) {
	std::cout << "Player " << player.getColor() + 1 << " is building a settlement." << std::endl;
	int tile = 0, corner = 0;

	if (!getImprovementLocation(screen, map, game, player, tile, corner)) {
		return false; //player has closed game, return from main
	}

	player.makeSettlement(map.getTileByIndex(tile), corner);
	return true;
}

bool getImprovementLocation(Display screen, CatanBoard map, GameController game, Player player, int &tile, int &corner) {
	tile = game.playerSelectTile(screen, map);
	if (tile == -1) {
		return false;			//player has closed the game, need to return main (before entering next while loop)
	}
	refreshScreen(screen, map, game);
	corner = game.playerSelectOpenCorner(screen, map, player, tile);
	if (corner == -1) {
		return false;			//player has closed the game, need to return main (brfore entering next while loop)
	}
	return true;
}

bool buildRoad(Display screen, CatanBoard map, GameController &game, Player &player, bool initialPlace) {
	std::cout << "Player " << player.getColor() + 1 << " is building a road." << std::endl;
	int corner1 = 0, corner2 = 0, tile = 0;

	if (!getRoadLocation(screen, map, game, player, tile, corner1, corner2)) {
		return false; //player has closed game, return from main
	}
	
	player.makeRoad(map.getTileByIndex(tile), corner1, corner2);
	return true;
}

bool getRoadLocation(Display screen, CatanBoard map, GameController game, Player player, int& tile, int& corner1, int& corner2) {
	tile = game.playerSelectTile(screen, map);
	if (tile == -1) {
		return false;			//player has closed the game, need to return main (brfore entering next while loop)
	}
	refreshScreen(screen, map, game);
	corner1 = game.playerSelectOwnedCorner(screen, map, player, tile);	//player must slect a tile they can reach by road or have a settlement on
	if (corner1 == -1) {
		return false;			//player has closed the game, need to return main (brfore entering next while loop)
	}
	refreshScreen(screen, map, game);
	corner2 = game.playerSelectAdjacentCorner(screen, map, player, tile, corner1);	//player must select a corner adjacent to the above selection
	if (corner2 == -1) {
		return false;			//player has closed the game, need to return main (brfore entering next while loop)
	}
	return true;
}

void printBuildings(Display screen, GameController game) {
	coords_t imageCoords;
	coords_t centerCoords = screen.center();
	int tileSize = screen.getTileSize();
	for (int i = 0; i < game.getNumberOfPlayers(); i++) {						//for every player
		for (int j = 0; j < game.getPlayer(i).getNumberOfRoads(); j++) {		//print every road
			imageCoords = game.getPlayer(i).getRoad(j).getImageLocation(tileSize);
			imageCoords.x -= tileSize / 4;
			imageCoords.y -= tileSize / 4;
			screen.placeTexture(32 + (64 * game.getPlayer(i).getRoad(j).getDirection()), 224 + (64 * game.getPlayer(i).getColor()), centerCoords.x + imageCoords.x, centerCoords.y + imageCoords.y, 64, 64);
		}
	}
	for (int i = 0; i < game.getNumberOfPlayers(); i++) {
		for (int j = 0; j < game.getPlayer(i).getNumberOfSettlements(); j++) {	//print every settlement
			imageCoords = imageCoords = game.getPlayer(i).getSettlement(j).getCenter(tileSize);
			screen.placeTexture(0, 224 + ( 64 * game.getPlayer(i).getColor()), centerCoords.x + imageCoords.x - 16, centerCoords.y + imageCoords.y - 16, 32, 32);
		}
		for (int j = 0; j < game.getPlayer(i).getNumberOfCities(); j++) {		//print every city
			imageCoords = imageCoords = game.getPlayer(i).getCity(j).getCenter(tileSize);
			screen.placeTexture(0, 256 + (32 * game.getPlayer(i).getColor()), centerCoords.x + imageCoords.x - 16, centerCoords.y + imageCoords.y - 16, 32, 32);
		}
	}
}