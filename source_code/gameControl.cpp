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

int GameController::playerSelectCornerRoad(Display screen, CatanBoard map, int tileSelection, bool* possibleCorners) {
	std::cout << "Please select a corner." << std::endl;
	coords_t coords;
	int cornerSelection = -1;
	int validCorner1, validCorner2;
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
	for (int i = 0; i < 6; i++) {
		possibleCorners[i] = 0;
	}
	validCorner1 = cornerSelection - 1;
	validCorner2 = cornerSelection + 1;
	if (validCorner1 < 0) {
		validCorner1 += 6;
	}
	if (validCorner2 > 5) {
		validCorner1 -= 6;
	}

	possibleCorners[validCorner1] = 1;		//only allow the corners right next to selection
	possibleCorners[validCorner2] = 1;
	screen.clearButtons();
	screen.update();
	return cornerSelection;
}

int GameController::playerSelectCorner(Display screen, CatanBoard map, int tileSelection) {
	std::cout << "Please select a corner." << std::endl;
	coords_t coords;
	int cornerSelection = -1;
	int xHover, yHover, resultHover, xClick, yClick, resultClick;
	for (int i = 0; i < 6; i++) {
		coords = map.getCornerCoords(tileSelection, i, screen.getTileSize());					//get each corner for selected tile
		coords.x -= (screen.getTileSize() / 8) - screen.center().x;			//move x
		coords.y -= (screen.getTileSize() / 8) - screen.center().y;			//move y
		screen.makeButton(coords.x, coords.y, screen.getTileSize() / 4, screen.getTileSize() / 4, true);
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

/*
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
	if (!initialPlace) {
		for (int i = 0; i < 6; i++) {
			possibleCorner = HexLoc::combine(tile, i);
			possibleCorners[i] = false;		//default to false 
			for (int j = 0; j < player.getNumberOfRoads(); j++) {
				if (player.getRoad(j).containsCorner(possibleCorner)) {
					//spot is open
					possibleCorners[i] = true;		//allow that corner to be selected
				}
			}
		}
	}
	else {//on initial place, the player must select the corner they placed thier settlement on
		for (int i = 0; i < 6; i++) {
			possibleCorners[i] = false;
			possibleCorner = HexLoc::combine(tile, i);
			for (int j = 0; j < player.getNumberOfSettlements(); j++) {
				if (player.getSettlement(j).isLocationOpen(possibleCorner)) {
					possibleCorners[i] = true;
				}
			}
		}
	}
	return playerSelectCorner(screen, map, tileSelection, possibleCorners);
}
*/
HexLoc GameController::playerSelectAdjacentCorner(Display screen, CatanBoard map, GameController game, Player player, int tile, int corner1) {
	std::cout << "Please select an adjacent corner to make your road." << std::endl;
	cube_t tileArray[3];
	int cornerArray[3];
	HexLoc locationArray[3];
	int cornerSelection;
	tileArray[0] = map.getTileByIndex(tile);
	tileArray[1] = map.getNeighbor(tileArray[0], corner1);
	tileArray[2] = map.getNeighbor(tileArray[0], corner1 + 1);

	cornerArray[0] = corner1 + 1;
	if (cornerArray[0] == 6) {
		cornerArray[0] = 0;
	}
	cornerArray[1] = cornerArray[0] + 2;
	cornerArray[2] = cornerArray[1] + 2;

	for (int i = 0; i < 3; i++) {
		locationArray[i] = HexLoc::combine(tileArray[i], cornerArray[i]);
	}
	coords_t coords;
	cornerSelection = -1;
	int xHover, yHover, resultHover, xClick, yClick, resultClick;
	for (int i = 0; i < 3; i++) {		//make three buttons adjacent to tileSelection, corner
		coords = map.getCornerCoords(tileArray[i], cornerArray[i], screen.getTileSize());
		coords.x -= (screen.getTileSize() / 8) - screen.center().x;			//move x
		coords.y -= (screen.getTileSize() / 8) - screen.center().y;			//move y
		screen.makeButton(coords.x, coords.y, screen.getTileSize() / 4, screen.getTileSize() / 4, true);
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
				return HexLoc();	//make sure to return main
			}
		}
	}
	screen.clearButtons();
	screen.update();


	return locationArray[cornerSelection];		
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
			if (player.getRoad(i).containsCorner(HexLoc::combine(tile, corner1)) || player.getRoad(i).containsCorner(HexLoc::combine(tile, corner2))) {
				validTile = true;					//flag that the player is in fact connected
			}
		}
	}
	else {
		int index = player.getNumberOfRoads();		//one of the roads corners must exactly match the corresponding settlement settlement
		HexLoc location = player.getSettlement(index).getLocation();
		if (location == HexLoc::combine(tile, corner1) || location == HexLoc::combine(tile, corner2)) {
			validTile = true;
		}
	}

	//check if any player blocks the location
	for (int i = 0; i < numberOfPlayers; i++) {
		for (int j = 0; j < playerList[i].getNumberOfRoads(); j++) {
			Road road = playerList[i].getRoad(j);
			if (!road.containsCorner(HexLoc::combine(tile, corner1)) && !road.containsCorner(HexLoc::combine(tile, corner2))) {		//to block a road, both corners must be used by the same road
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
			if (player.getRoad(i).containsCorner(HexLoc::combine(tile, corner))) {
				validTile = true;					//flag that the player is in fact connected
				std::cout << "you can reach this tile!" << std::endl;
			}
		}
	} 

	//check if any player blocks the location
	for (int i = 0; i < numberOfPlayers; i++) {
		for (int j = 0; j < playerList[i].getNumberOfSettlements(); j++) {
			if (!playerList[i].getSettlement(j).isCornerOpen(tile, corner)) {
				return false;
				std::cout << "player " << i << "'s settlement blocks you!" << std::endl;
			}
		}
		for (int j = 0; j < playerList[i].getNumberOfCities(); j++) {
			if (!playerList[i].getCity(j).isCornerOpen(tile, corner)) {
				return false;
				std::cout << "player " << i << "'s city blocks you!" << std::endl;
			}
		}
	}
	std::cout << validTile << std::endl;
	return validTile;
}

Road GameController::convertToRoad(HexLoc loc1, HexLoc loc2) {
	//decide tile -- Road needs a tile that contains both corners, se we need to find a sutable tile
	cube_t tile;
	HexLoc temp, temp2;
	int newCorner;
	//arbitrarily choose loc1's tile to try
	tile = loc1.getHexCoords();
	for (int i = 0; i < 6; i++) {
		//try all corners of this tile
		if (HexLoc::combine(tile, i) == loc2) {
			//tile1 has both corners!
			newCorner = i;
			return Road(tile, loc1.getPos(), newCorner);
		}
	}

	//maybe loc2's tile will work?
	tile = loc2.getHexCoords();
	for (int i = 0; i < 6; i++) {
		//try all corners of this tile
		if (HexLoc::combine(tile, i) == loc2) {
			//tile1 has both corners!
			newCorner = i;
			return Road(tile, loc2.getPos(), newCorner);
		}
	}
	//if the tiles touch, then the above should have found a sutable tile, and the function should have returned by now
	//however it is possible to select two tiles that do not touch, but have valid corners for a road
	//now we will try to any tile touching loc1's tile to use
	for (int i = 0; i < 6; i++) {
		tile = map.getNeighbor(loc1.getHexCoords(), i);	//get some adjacent tile to loc1
		for (int j = 0; j < 6; j++) {
			temp = HexLoc::combine(tile, j);
			if (j + 1 == 6) {
				temp2 = HexLoc::combine(tile, 0);
			}
			else {
				temp2 = HexLoc::combine(tile, j + 1);
			}
			if ((temp == loc1 || temp == loc2) && (temp2 == loc1 || temp2 == loc2)) {
				//this tile will do!
				newCorner = j;
				return Road(tile, j, j + 1);
			}
		}
	}

	//the above should have worked, but we can still try again with the other locations tile
	for (int i = 0; i < 6; i++) {
		tile = map.getNeighbor(loc2.getHexCoords(), i);	//get some adjacent tile to loc1
		for (int j = 0; j < 6; j++) {
			temp = HexLoc::combine(tile, j);
			if (j + 1 == 6) {
				temp2 = HexLoc::combine(tile, 0);
			}
			else {
				temp2 = HexLoc::combine(tile, j + 1);
			}
			if ((temp == loc1 || temp == loc2) && (temp2 == loc1 || temp2 == loc2)) {
				//this tile will do!
				newCorner = j;
				return Road(tile, j, j + 1);
			}
		}
	}

	//at this point it is safe to assume the input is invalid, return default constructor for road, and print error
	std::cout << "Error, no road could be found for the given paramameters: " << loc1.getHexCoords().x << ", " << loc1.getHexCoords().y << "< " << loc1.getHexCoords().z << ", " << loc1.getPos() << " and " << loc2.getHexCoords().x << ", " << loc2.getHexCoords().y << "< " << loc2.getHexCoords().z << ", " << loc2.getPos();
	return Road();
}


void GameController::populateWithAdjacentTiles(HexLoc location, Tile* tileArray) {
	cube_t hexArray[3];
	int corner = location.getPos();

	hexArray[0] = location.getHexCoords();
	hexArray[1] = map.getNeighbor(hexArray[0], corner);
	hexArray[2] = map.getNeighbor(hexArray[0], corner + 1);

	for (int i = 0; i < 3; i++) {
		tileArray[i] = map.getTileObj(hexArray[i]);
	}
}