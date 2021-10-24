#ifndef BUTTON_H
#define BUTTON_H

#include "SDL2/SDL.h"

class Button {
public:
	Button();
	Button(SDL_Rect box, bool show = false);
	Button(int x, int y, int w, int h, bool show = false);

	bool checkX(int value);
	bool checkY(int value);
	bool checkCoords(int x, int y);

	SDL_Rect getBox() { return box; }

	void hide() { isShown = false; }
	void show() { isShown = true; }
	
private:
	SDL_Rect box;
	bool isShown;
};

#endif