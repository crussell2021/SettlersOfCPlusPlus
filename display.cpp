#include "display.h"

Display::Display() {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("Main", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, 0);

	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
	setBackground(25, 125, 255);
	std::string spriteFile = "test.png";
	loadImage(spriteFile.c_str());
}

Display::Display(std::string spriteFile) {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("Main", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, 0);

	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
	setBackground(25, 125, 255);
	loadImage(spriteFile.c_str());
}

void Display::loadImage(std::string fileName) {					//if only one sprite page is used, this function isnt needed
	spritePage = IMG_LoadTexture(renderer, fileName.c_str());	//an array is needed if multiple sprite pages
}

void Display::setBackground(int red, int green, int blue) {
	SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Display::placeTexture(int xClip, int yClip, int xDst, int yDst) {
	SDL_Rect clip, destination;
	clip.x = xClip;
	clip.y = yClip;
	destination.x = xDst;
	destination.y = yDst;
	destination.w = destination.h = tileSize;
	clip.w = clip.h = tileSize;
	SDL_RenderCopy(renderer, spritePage, &clip, &destination);
}

void Display::update() {
	SDL_RenderPresent(renderer);
}

void Display::cleanup() {
	SDL_DestroyTexture(spritePage);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}