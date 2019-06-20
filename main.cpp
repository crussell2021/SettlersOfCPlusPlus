// SettlersOfC++ main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "display.h"

int main(int argc, char* argv[]) {
	Display display("test.png");

	SDL_Rect tileMap[19];
	tileMap[9].x = (display.getScreenWidth() - display.getTileSize()) / 2;		//center tile, reference for all other tiles

	tileMap[1].x = tileMap[17].x = tileMap[9].x;

	tileMap[0].x = tileMap[8].x = tileMap[16].x = (tileMap[9].x - display.getTileSize());
	tileMap[2].x = tileMap[10].x = tileMap[18].x = (tileMap[9].x + display.getTileSize());

	tileMap[7].x = tileMap[9].x - (2 * display.getTileSize());
	tileMap[11].x = tileMap[9].x + (2 * display.getTileSize());

	tileMap[4].x = tileMap[13].x = (tileMap[9].x + (display.getTileSize()/2));
	tileMap[5].x = tileMap[14].x = (tileMap[9].x - (display.getTileSize() / 2));

	tileMap[6].x = tileMap[15].x = (tileMap[9].x + (3 * display.getTileSize() / 2));
	
	tileMap[3].x = tileMap[12].x = (tileMap[9].x - (3 * display.getTileSize() / 2));

	tileMap[9].y = (display.getScreenHeight() - display.getTileSize()) / 2;
	
	tileMap[7].y = tileMap[8].y = tileMap[10].y = tileMap[11].y = tileMap[9].y;
	tileMap[3].y = tileMap[4].y = tileMap[5].y = tileMap[6].y = tileMap[9].y - (3 * display.getTileSize() / 4);
	tileMap[12].y = tileMap[13].y = tileMap[14].y = tileMap[15].y = tileMap[9].y + (3 * display.getTileSize() / 4);
	tileMap[0].y = tileMap[1].y = tileMap[2].y = tileMap[9].y - (3 * display.getTileSize() / 2);
	tileMap[16].y = tileMap[17].y = tileMap[18].y = tileMap[9].y + (3 * display.getTileSize() / 2);


	
	for (int i = 0; i < 19; i++) {
		display.placeTexture(0, 0, tileMap[i].x, tileMap[i].y);
	}
	display.update();
	bool loop = true;
	while (loop) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				loop = false;
			}
		}
	}
	display.cleanup();
	return 0;
}
