#include "gameControl.h"

void GameController::addPlayers(int number) {
	int color = 0;
	for (int i = 0; i < number; i++) {
		playerList[numberOfPlayers++] = Player(color++);
	}
}

/*
bool GameController::addBuilding(Display screen, Player player, CatanBoard map) {	//this function works, but the screen cannot be cleared from inside this class
	std::cout << "Player " << player.getColor() + 1 << " is building a settlement." << std::endl;
	int tile, corner;
	tile = playerSelectTile(screen, map);
	if (tile == -1) {
		return false;			//player has closed the game, need to return main (brfore entering next while loop)
	}
	corner = playerSelectCorner(screen, map, tile);
	if (corner == -1) {
		return false;			//player has closed the game, need to return main (brfore entering next while loop)
	}
	player.makeSettlement(map.getTileByIndex(tile), corner);
	return true;
}
*/

int GameController::playerSelectTile(Display screen, CatanBoard map) {
	std::cout << "Please select a tile." << std::endl;
	coords_t coords;//temp variable for button position
	for (int i = 0; i < map.getNumberOfTiles(); i++) {
		coords = map.getTileCenter(i, screen.getTileSize());					//get center for each tile
		coords.x -= (screen.getTileSize() / 4) - screen.center().x;									//move x to left size of tile
		coords.y -= (screen.getTileSize() / 4) - screen.center().y;									//move y to top of rectangle inside of hex, making the button most of the hex's size
		screen.makeButton(coords.x, coords.y, screen.getTileSize() / 2, screen.getTileSize() / 2, true);
	}
	int tileSelection = -1, cornerSelection = -1;
	int xHover, yHover, resultHover, xClick, yClick, resultClick;
	while (tileSelection == -1) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_MOUSEMOTION) {
				xHover = event.button.x;
				yHover = event.button.y;
				resultHover = screen.checkButtons(xHover, yHover);
				if (resultHover == -1) {
					//no tile was found
					screen.hideButtons();
					screen.needUpdate();
				}
				else {
					screen.highlightButton(resultHover);
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				xClick = event.button.x;
				yClick = event.button.y;
				resultClick = screen.checkButtons(xClick, yClick);
				if (resultClick == -1) {
					//no tile was found
				}
				else {
					tileSelection = resultClick;
				}
			}
			if (event.type == SDL_QUIT) {
				screen.cleanup();
				return -1; //make sure to return main
			}
			if (screen.checkUpdate()) {
				screen.update();
			}
		}
	}
	screen.update();
	screen.clearButtons();
	return tileSelection;
}

int GameController::playerSelectCorner(Display screen, CatanBoard map, int tileSelection, bool* possibleCorners) {
	std::cout << "Please select a corner." << std::endl;
	coords_t coords;
	int cornerSelection = -1;
	int xHover, yHover, resultHover, xClick, yClick, resultClick;
	for (int i = 0; i < 6; i++) {
		if (&possibleCorners[i]) {
			coords = map.getCornerCoords(tileSelection, i, screen.getTileSize());					//get each corner for selected tile
			coords.x -= (screen.getTileSize() / 8) - screen.center().x;			//move x
			coords.y -= (screen.getTileSize() / 8) - screen.center().y;			//move y
			screen.makeButton(coords.x, coords.y, screen.getTileSize() / 4, screen.getTileSize() / 4, true);
		}
	}
	while (cornerSelection == -1) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_MOUSEMOTION) {
				xHover = event.button.x;
				yHover = event.button.y;
				resultHover = screen.checkButtons(xHover, yHover);
				if (resultHover == -1) {
					//no tile was found
					screen.hideButtons();
					screen.needUpdate();
				}
				else {
					screen.highlightButton(resultHover);
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				xClick = event.button.x;
				yClick = event.button.y;
				resultClick = screen.checkButtons(xClick, yClick);
				if (resultClick == -1) {
					//no tile was found
				}
				else {
					cornerSelection = resultClick;
				}
			}
			if (event.type == SDL_QUIT) {
				screen.cleanup();
				return -1;	//make sure to return main
			}
		}
	}
	screen.clearButtons();
	screen.update();
	return cornerSelection;
}

int GameController::playerSelectOpenCorner(Display screen, CatanBoard map, Player player, int tileSelection, bool initialPlace) {
	bool possibleCorners[6];
	HexLoc possibleCorner;
	cube_t tile = map.getTileByIndex(tileSelection);
	for (int i = 0; i < 6; i++) {
		possibleCorner = HexLoc::combine(tile, i);
		if (checkImprovement(possibleCorner, player, initialPlace)) {
			//spot is open
			possibleCorners[i] = true;
		}
		else {
			//spot taken
			possibleCorners[i] = false;
		}
	}
	return playerSelectCorner(screen, map, tileSelection, possibleCorners);
}

int GameController::playerSelectOwnedCorner(Display screen, CatanBoard map, Player player, int tileSelection, bool initialPlace) {
	bool possibleCorners[6];
	HexLoc possibleCorner;
	cube_t tile = map.getTileByIndex(tileSelection);
	for (int i = 0; i < 6; i++) {
		possibleCorner = HexLoc::combine(tile, i);
		if () {
			//spot is open
			possibleCorners[i] = true;
		}
		else {
			//spot taken
			possibleCorners[i] = false;
		}
	}
	return playerSelectCorner(screen, map, tileSelection, possibleCorners);
}

int GameController::playerSelectAdjacentCorner(Display screen, CatanBoard map, Player player, int tileSelection, int cornerSelection, bool initialplace) { 
	
}

bool GameController::checkImprovement(HexLoc location, Player player, bool initialPlace) {
	bool validTile = false;
	HexLoc building;
	//check if the player can reach the corner through their roads
	if (!initialPlace) {							//if this is the initial place, the player will not need to meet this check
		validTile = false;
		for (int i = 0; i < player.getNumberOfRoads(); i++) {
			if (player.getRoad(i).containsCorner(location)) {
				validTile = true;					//flag that the player is in fact connected
				std::cout << "you can reach this tile!" << std::endl;
			}
		}
	}
	else { validTile = true; }

	//check if any player blocks the location
	for (int i = 0; i < numberOfPlayers; i++) {
		for (int j = 0; j < playerList[i].getNumberOfSettlements(); j++) {
			building = playerList[i].getSettlement(j).getHexLoc();
			if (location == building) {
				return false;
				std::cout << "player " << i << "'s settlement blocks you!" << std::endl;
			}
		}
		for (int j = 0; j < playerList[i].getNumberOfCities(); j++) {
			building = playerList[i].getCity(j).getHexLoc();
			if (location == building) {
				return false;
				std::cout << "player " << i << "'s city blocks you!" << std::endl;
			}
		}
	}
	return validTile;
}

bool GameController::checkRoad(cube_t tile, int corner1, int corner2, Player player, bool initialPlace) {
	bool validTile = false;
	//check if the player can reach either corner through their roads
	if (!initialPlace) {		//the player must be connected by roads, unless it is one of the initial roads
		for (int i = 0; i < player.getNumberOfRoads(); i++) {
			if (player.getRoad(i).checkCorner(tile, corner1) || player.getRoad(i).checkCorner(tile, corner2)) {
				validTile = true;					//flag that the player is in fact connected
				std::cout << "you can reach this tile!" << std::endl;
			}
		}
	}
	else {
		int index = player.getNumberOfRoads();		//one of the roads corners must exactly match the corresponding settlement settlement
		if (player.getSettlement(index).checkLocation(tile, corner1) || player.getSettlement(index).checkLocation(tile, corner2)) {
			validTile = true;
		}
	}

	//check if any player blocks the location
	for (int i = 0; i < numberOfPlayers; i++) {
		for (int j = 0; j < playerList[i].getNumberOfRoads(); j++) {
			Road road = playerList[i].getRoad(j);
			if (!road.checkCorner(tile, corner1) && !road.checkCorner(tile, corner2)) {		//to block a road, both corners must be used by the same road
				return false;
				std::cout << "player " << i << "'s road is already there!" << std::endl;
			}
		}
	}
	std::cout << validTile << std::endl;
	return validTile;
}

bool GameController::checkSettlement(cube_t tile, int corner, Player player, bool initialPlace) {
	bool validTile = true;
	//check if the player can reach the corner through their roads
	if (!initialPlace) {							//if this is the initial place, the player will not need to meet this check
		validTile = false;
		for (int i = 0; i < player.getNumberOfRoads(); i++) {
			if (player.getRoad(i).checkCorner(tile, corner)) {
				validTile = true;					//flag that the player is in fact connected
				std::cout << "you can reach this tile!" << std::endl;
			}
		}
	} 

	//check if any player blocks the location
	for (int i = 0; i < numberOfPlayers; i++) {
		for (int j = 0; j < playerList[i].getNumberOfSettlements(); j++) {
			if (!playerList[i].getSettlement(j).checkCorner(tile, corner)) {
				return false;
				std::cout << "player " << i << "'s settlement blocks you!" << std::endl;
			}
		}
		for (int j = 0; j < playerList[i].getNumberOfCities(); j++) {
			if (!playerList[i].getCity(j).checkCorner(tile, corner)) {
				return false;
				std::cout << "player " << i << "'s city blocks you!" << std::endl;
			}
		}
	}
	std::cout << validTile << std::endl;
	return validTile;
}

/*
bool GameController::checkRoad(cube_t tile, int corner1, int corner2, Player player, bool* initialPlace) {
	bool validTile = false;
	//check if the player can reach either corner through their roads
	if (!initialPlace) {		//the player must be connected by roads, unless it is one of the initial roads
		for (int i = 0; i < player.getNumberOfRoads(); i++) {
			if (player.getRoad(i).checkCorner(tile, corner1) || player.getRoad(i).checkCorner(tile, corner2)) {
				validTile = true;					//flag that the player is in fact connected
				std::cout << "you can reach this tile!" << std::endl;
			}
		}
	}
	else {
		int index = player.getNumberOfRoads();		//one of the roads corners must exactly match the corresponding settlement settlement
		if (player.getSettlement(index).checkLocation(tile, corner1) || player.getSettlement(index).checkLocation(tile, corner2)) {
			validTile = true;
		}
	}

	//check if any player blocks the location
	for (int i = 0; i < numberOfPlayers; i++) {
		for (int j = 0; j < playerList[i].getNumberOfRoads(); j++) {
			Road road = playerList[i].getRoad(j);
			if (!road.checkCorner(tile, corner1) && !road.checkCorner(tile, corner2)) {		//to block a road, both corners must be used by the same road
				return false;
				std::cout << "player " << i << "'s road is already there!" << std::endl;
			}
		}
	}
	std::cout << validTile << std::endl;
	return validTile;
}
*/

void GameController::initialResources() {
	Improvement secondSettlement;
	cube_t tile;
	int tileNumber;
	tileType resource;
	for (int i = 0; i < numberOfPlayers; i++) {
		secondSettlement = playerList[i].getSettlement(1);
		for (int i = 0; i < 3; i++) {
			tile = secondSettlement.getHexCoords(i);
			tileNumber = map.getTileByCoords(tile);
			resource = map.getResourceAt(tileNumber);
			playerList[i].gainResource(resource);
		}
	}
}