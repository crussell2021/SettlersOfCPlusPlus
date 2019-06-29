#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <iostream>
#include "player.h"
#include "SDL.h"
#include "display.h"
#include "board.h"
#include "hexLoc.h"

class GameController {
public: 
	GameController() : map(3) { numberOfPlayers = 0; }
	void addPlayers(int players);
	Player getPlayer(int index) { return playerList[index]; }
	Player& getPlayerPointer(int index) { return playerList[index]; }
	int getNumberOfPlayers() { return numberOfPlayers; }

	int playerSelectTile(Display screen, CatanBoard map);
	int playerSelectCorner(Display screen, CatanBoard map, int tileSelection, bool* possibleCorners);

	int playerSelectOpenCorner(Display screen, CatanBoard map, Player player, int tileSelection, bool initialplace = false);
	int playerSelectOwnedCorner(Display screen, CatanBoard map, Player player, int tileSelection, bool initialplace = false);
	int playerSelectAdjacentCorner(Display screen, CatanBoard map, Player player, int tileSelection, int cornerSelection, bool initialplace = false);

	bool checkImprovement(HexLoc location, Player player, bool initialPlace = false);  //checks if the location is availible currently on the map
	bool checkSettlement(cube_t tile, int corner, Player player, bool initialPlace = false);
	bool checkRoad(cube_t tile, int corner1, int corner2, Player player, bool initialPlace = false);
	
	//bool addBuilding(Display screen, Player player, CatanBoard map);	//closing the screen will freeze the program, make sure if this returns false to return from main

	//void checkRoll(int roll);
	void initialResources();
	
	CatanBoard map;

	friend bool operator==(const HexLoc& loc1, const HexLoc& loc2);

private:
	int numberOfPlayers;
	Player playerList[4];

};

bool operator==(const HexLoc& loc1, const HexLoc& loc2);

#endif