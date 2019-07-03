// SettlersOfC++ main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <fstream>
#include "display.h"
#include "gameControl.h"

void printPlayerPanels(Display screen, GameController game);
void printBoard(Display screen, CatanBoard map);
void printBuildings(Display screen, GameController game);

bool buildRoad(Display screen, CatanBoard map, GameController& game, Player& player, bool initialPlace = false);
bool buildSettlement(Display screen, CatanBoard map, GameController& game, Player& player);

bool initialPlacement(Display screen, GameController& game, Player& player);

//bool getAdjacentCorner(Display screen, CatanBoard map, GameController game, Player player, int tile, int corner1, int* corner2);
bool getImprovementLocation(Display screen, CatanBoard map, GameController game, Player player, int& tile, int& corner);
bool getRoadLocation(Display screen, CatanBoard map, GameController game, Player player, int& tile, int& corner1, int& corner2, bool initialPlace);
bool getRoadLocation(Display screen, CatanBoard map, GameController game, Player player, int& tile, int& corner1, int& corner2);

void refreshScreen(Display screen, CatanBoard map, GameController game);

int main(int argc, char* argv[]) {
	Display display;
	display.loadSpritePage("128hexsetBuildingFrame2.png");
	GameController game;

	std::string responce;
	std::cout << "With this program, you can save a catan game you have in progress and then load it up later and continue playing." << std::endl << "Create  new game? (Y/N): " << std::endl;
	std::cin >> responce;

	std::fstream file;

	if (responce == "Y" || responce == "y") {
		int numberOfPlayers, numwood, numbrick, numsheep, numrock, numwheat, numdevCards, numSettlements, numRoads, numCities;
		int tile, corner1, corner2;
		std::cout << "How many players? ";
		std::cin >> numberOfPlayers;

		game.addPlayers(numberOfPlayers);

		refreshScreen(display, game.map, game);

		for (int i = 0; i < game.getNumberOfPlayers(); i++) {
			Player currentPlayer = (game.getPlayer(i));
			std::cout << "Creating player " << i + 1 << ". How many of each of the following did this player have?" << std::endl;
			std::cout << "Wood cards: ";
			std::cin >> numwood;
			game.getPlayerPointer(i).setNumberOfWood(numwood);
			std::cout << "Sheep cards: ";
			std::cin >> numsheep;
			game.getPlayerPointer(i).setNumberOfSheep(numsheep);
			std::cout << "Rock cards: ";
			std::cin >> numrock;
			game.getPlayerPointer(i).setNumberOfRock(numrock);
			std::cout << "Wheat cards: ";
			std::cin >> numwheat;
			game.getPlayerPointer(i).setNumberOfWheat(numwheat);
			std::cout << "Brick cards: ";
			std::cin >> numbrick;
			game.getPlayerPointer(i).setNumberOfBricks(numbrick);
			std::cout << "Developement Cards: ";
			std::cin >> numdevCards;
			game.getPlayerPointer(i).setNumberOfDevCards(numdevCards);
			std::cout << "Settlements: ";
			std::cin >> numSettlements;
			while (numSettlements > 5) {
				std::cout << "You can only have 5 settlements." << std::endl;
				std::cout << "Settlements: ";
				std::cin >> numSettlements;
			}
			std::cout << "Roads: ";
			std::cin >> numRoads;
			while (numRoads > 15) {
				std::cout << "You can only have 15 roads." << std::endl;
				std::cout << "Roads: ";
				std::cin >> numRoads;
			}
			std::cout << "Cities: ";
			std::cin >> numCities;
			while (numCities > 4) {
				std::cout << "You can only have 4 cities." << std::endl;
				std::cout << "Cities: ";
				std::cin >> numCities;
			}

			refreshScreen(display, game.map, game);

			for (int j = 0; j < numSettlements; j++) {
				std::cout << "Place a settlement." << std::endl;
				if (!getImprovementLocation(display, game.map, game, game.getPlayer(i), tile, corner1)) {
					return -1; //player has closed game, return from main
				}
				game.getPlayerPointer(i).makeSettlement(game.map.getTileByIndex(tile), corner1);
				refreshScreen(display, game.map, game);
			}

			for (int j = 0; j < numRoads; j++) {
				std::cout << "Place a road." << std::endl;
				if (!getRoadLocation(display, game.map, game, game.getPlayer(i), tile, corner1, corner2)) {
					return -1; //player has closed game, return from main
				}
				game.getPlayerPointer(i).makeRoad(game.map.getTileByIndex(tile), corner1, corner2);
				refreshScreen(display, game.map, game);
			}

			for (int j = 0; j < numCities; j++) {
				std::cout << "Place a city." << std::endl;
				if (!getImprovementLocation(display, game.map, game, game.getPlayer(i), tile, corner1)) {
					return -1; //player has closed game, return from main
				}
				game.getPlayerPointer(i).makeCity(game.map.getTileByIndex(tile), corner1);
				refreshScreen(display, game.map, game);
			}
		}

		std::cout << "Close the window when your ready." << std::endl;

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

		std::cout << "Please enter the file name ending in .txt to save the game under: ";
		std::cin >> responce;
										
		file.open(responce.c_str(), std::ios::out);							

		while (file.fail()) {										
			std::cout << "could not open file \r\n";
			std::cout << "Please enter the file name ending in .txt to save the game under: \r\n";
			std::cin >> responce;
			file.open(responce.c_str(), std::ios::out);
		}

		file << game.getNumberOfPlayers() << std::endl;

		Improvement settlement;
		Road road;

		for (int i = 0; i < numberOfPlayers; i++) {
			file << game.getPlayerPointer(i).getNumberOfWood() << std::endl;
			file << game.getPlayerPointer(i).getNumberOfSheep() << std::endl;
			file << game.getPlayerPointer(i).getNumberOfRock() << std::endl;
			file << game.getPlayerPointer(i).getNumberOfWheat() << std::endl;
			file << game.getPlayerPointer(i).getNumberOfBricks() << std::endl;
			file << game.getPlayerPointer(i).getNumberOfDevCards() << std::endl;
			file << game.getPlayerPointer(i).getNumberOfSettlements() << std::endl;
			for (int j = 0; j < game.getPlayerPointer(i).getNumberOfSettlements(); j++) {
				settlement = game.getPlayerPointer(i).getSettlement(j);
				file << settlement.getX() << "\t" << settlement.getY() << "\t" << settlement.getZ() << "\t" << settlement.getCorner() << std::endl;
			}
			file << game.getPlayerPointer(i).getNumberOfCities() << std::endl;
			for (int j = 0; j < game.getPlayerPointer(i).getNumberOfCities(); j++) {
				settlement = game.getPlayerPointer(i).getCity(j);
				file << settlement.getX() << "\t" << settlement.getY() << "\t" << settlement.getZ() << "\t" << settlement.getCorner() << std::endl;
			}
			file << game.getPlayerPointer(i).getNumberOfRoads() << std::endl;
			for (int j = 0; j < game.getPlayerPointer(i).getNumberOfRoads(); j++) {
				road = game.getPlayerPointer(i).getRoad(j);
				file << road.getX() << "\t" << road.getY() << "\t" << road.getZ() << "\t" << road.getCorner(0) << "\t" << road.getCorner(1) << std::endl;
			}
		}
		std::cout << "Your game has been succesfully saved as \'" << responce << "\' . Restart the program and enter that name to view it when your ready." << std::endl;

	} else if (responce == "N" || responce == "n") {
		std::cout << "Please enter the file name to be loaded: ";
		std::cin >> responce;

		file.open(responce.c_str(), std::ios::in);

		while (file.fail()) {
			std::cout << "could not open file \r\n";
			std::cout << "Please enter the file name ending in .txt to save the game under: \r\n";
			std::cin >> responce;
			file.open(responce.c_str(), std::ios::in);
		}

		int input, numberOfPlayers, tileX, tileY, tileZ, corner1, corner2;
		cube_t tile;
		file >> numberOfPlayers;
		game.addPlayers(numberOfPlayers);

		refreshScreen(display, game.map, game);

		for (int i = 0; i < numberOfPlayers; i++) {
			//resources
			file >> input;
			game.getPlayerPointer(i).setNumberOfWood(input);
			file >> input;
			game.getPlayerPointer(i).setNumberOfSheep(input);
			file >> input;
			game.getPlayerPointer(i).setNumberOfRock(input);
			file >> input;
			game.getPlayerPointer(i).setNumberOfWheat(input);
			file >> input;
			game.getPlayerPointer(i).setNumberOfBricks(input);
			file >> input;
			game.getPlayerPointer(i).setNumberOfDevCards(input);

			//buildings
			//settlements
			file >> input;
			for (int j = 0; j < input; j++) {
				file >> tileX >> tileY >> tileZ >> corner1;
				tile = { tileX, tileY, tileZ };
				game.getPlayerPointer(i).makeSettlement(tile, corner1);
			}
			//cities
			file >> input;
			for (int j = 0; j < input; j++) {
				file >> tileX >> tileY >> tileZ >> corner1;
				tile = { tileX, tileY, tileZ };
				game.getPlayerPointer(i).makeCity(tile, corner1);
			}
			//roads
			file >> input;
			for (int j = 0; j < input; j++) {
				file >> tileX >> tileY >> tileZ >> corner1 >> corner2;
				tile = { tileX, tileY, tileZ };
				game.getPlayerPointer(i).makeRoad(tile, corner1, corner2);
			}
		}

		refreshScreen(display, game.map, game);

		//loop to keep window open
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
	}
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
		screen.placeSolidRectangle(52, 82, 127, panelX, panelY, width, height);
		screen.printText("Player " + std::to_string(i + 1), panelX + 5, panelY + 5);
		screen.printText("Wood: " + std::to_string(game.getPlayer(i).getNumberOfWood()) + "  Bricks: " + std::to_string(game.getPlayer(i).getNumberOfBricks()), panelX + 10, panelY + 32);
		screen.printText("Sheep: " + std::to_string(game.getPlayer(i).getNumberOfSheep()) + "  Wheat: " + std::to_string(game.getPlayer(i).getNumberOfWheat()), panelX + 10, panelY + 64);
		screen.printText("Rock: " + std::to_string(game.getPlayer(i).getNumberOfRock()) + "  Development Cards: " + std::to_string(game.getPlayer(i).getNumberOfDevCards()), panelX + 10, panelY + 96);
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

bool initialPlacement(Display screen, GameController& game, Player& player) {
	std::cout << "Player " << player.getColor() + 1 << " is placing an initial settlement." << std::endl;
	int tile, corner1;
	HexLoc location1, location2;
	if (!getImprovementLocation(screen, game.map, game, player, tile, corner1)) {
		return false; //player has closed game, return from main
	}
	player.makeSettlement(game.map.getTileByIndex(tile), corner1);
	refreshScreen(screen, game.map, game);
	location1 = HexLoc::combine(game.map.getTileByIndex(tile), corner1);
	location2 = game.playerSelectAdjacentCorner(screen, game.map, game, player, tile, corner1);
	if (location2 == HexLoc()) {
		return false; //player has closed game, return from main
	}

	player.makeRoad(game.convertToRoad(location1, location2));
	return true;
}


bool buildSettlement(Display screen, CatanBoard map, GameController &game, Player &player) {
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

	if (!getRoadLocation(screen, map, game, player, tile, corner1, corner2, initialPlace)) {
		return false; //player has closed game, return from main
	}
	
	player.makeRoad(map.getTileByIndex(tile), corner1, corner2);
	return true;
}

bool getRoadLocation(Display screen, CatanBoard map, GameController game, Player player, int& tile, int& corner1, int& corner2) {
	bool corners[6] = { 1,1,1,1,1,1 };
	tile = game.playerSelectTile(screen, map);
	if (tile == -1) {
		return false;
	}
	refreshScreen(screen, map, game);
	corner1 = game.playerSelectCorner(screen, map, tile, corners);

	refreshScreen(screen, map, game);
	corner2 = game.playerSelectCorner(screen, map, tile, corners);
	return true;
}

bool getRoadLocation(Display screen, CatanBoard map, GameController game, Player player, int& tile, int& corner1, int& corner2, bool initialPlace) {
	if (!initialPlace) {
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
	}
	else {
		HexLoc location = player.getSettlement(player.getNumberOfSettlements() - 1).getHexLoc();
		tile = map.getTileByCoords( location.getHexCoords() );
		corner1 = location.getPos();
	}

	corner2 = game.playerSelectOwnedCorner(screen, map, player, tile, corner1);	//player must select a corner adjacent to the above selection
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
			imageCoords.y -= 2;
			imageCoords.x -= 2;
			screen.placeTexture(32 + (64 * game.getPlayer(i).getRoad(j).getOrientation()), 224 + (64 * game.getPlayer(i).getColor()), centerCoords.x + imageCoords.x, centerCoords.y + imageCoords.y, 64, 64);
		}
	}
	for (int i = 0; i < game.getNumberOfPlayers(); i++) {
		for (int j = 0; j < game.getPlayer(i).getNumberOfSettlements(); j++) {	//print every settlement
			imageCoords = game.getPlayer(i).getSettlement(j).getCenter(tileSize);
			screen.placeTexture(0, 224 + ( 64 * game.getPlayer(i).getColor()), centerCoords.x + imageCoords.x - 16, centerCoords.y + imageCoords.y - 16, 32, 32);
		}
		for (int j = 0; j < game.getPlayer(i).getNumberOfCities(); j++) {		//print every city
			imageCoords = game.getPlayer(i).getCity(j).getCenter(tileSize);
			screen.placeTexture(0, 256 + (64 * game.getPlayer(i).getColor()), centerCoords.x + imageCoords.x - 16, centerCoords.y + imageCoords.y - 16, 32, 32);
		}
	}
}