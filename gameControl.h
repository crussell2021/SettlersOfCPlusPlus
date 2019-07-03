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
	int playerSelectCorner(Display screen, CatanBoard map, int tileSelection);
	int playerSelectCornerRoad(Display screen, CatanBoard map, int tileSelection, bool* possibleCorners);

	//int playerSelectOpenCorner(Display screen, CatanBoard map, Player player, int tileSelection, bool initialplace = false);
	//int playerSelectOwnedCorner(Display screen, CatanBoard map, Player player, int tileSelection, bool initialplace = false);
	HexLoc playerSelectAdjacentCorner(Display screen, CatanBoard map, GameController game, Player player, int tile, int corner1);

	bool checkImprovement(HexLoc location, Player player, bool initialPlace = false);  //checks if the location is availible currently on the map
	bool checkSettlement(cube_t tile, int corner, Player player, bool initialPlace = false);
	bool checkRoad(cube_t tile, int corner1, int corner2, Player player, bool initialPlace = false);
	
	Road convertToRoad(HexLoc, HexLoc);

	//void checkRoll(int roll);
	//void initialResources();

	void populateWithAdjacentTiles(HexLoc, Tile*);
	
	CatanBoard map;

	friend bool operator==(const HexLoc& loc1, const HexLoc& loc2);

private:
	int numberOfPlayers;
	Player playerList[4];

};

bool operator==(const HexLoc& loc1, const HexLoc& loc2);

#endif