#ifndef DISPLAY_H
#define DISPLAY_H
#include "SDL.h"
#include "SDL_image.h"
#include <string>

class Display {
public:
	Display();
	Display(std::string spriteFile);

	void setBackground(int r, int g, int b);
	void placeTexture(int xClip, int yClip, int xDst, int yDst);
	void loadImage(std::string);

	int getScreenWidth() { return screenWidth; }
	int getScreenHeight() { return screenHeight; }
	int getTileSize() { return tileSize; }

	void update();
	void cleanup();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* spritePage;
	SDL_Event sdlEvent;

	const int screenWidth = 1280;
	const int screenHeight = 768;
	const int tileSize = 128;

};

#endif