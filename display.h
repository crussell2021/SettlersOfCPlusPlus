#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "button.h"

struct coords_t {
	int x;
	int y;

	coords_t(int x = 0, int y = 0) : x(x), y(y) {}

	coords_t& operator=(const coords_t& coords) {
		x = coords.x;
		y = coords.y;
		return *this;
	}

	coords_t operator+(const coords_t& coords) const {
		return coords_t(coords.x + x, coords.y + y);
	}

	bool operator==(const coords_t& coords) {
		return (x == coords.x && y == coords.y);
	}
};

class Display {
public:
	Display();

	void loadSpritePage(std::string);

	void placeTexture(int xClip, int yClip, int xDst, int yDst, int clipSize = tileSize, int dstSize = tileSize);
	void placeTexture(int xClip, int yClip, int xDst, int yDst, int wClipSize, int hClipSize, int wDstSize, int hDstSize);
	void placeSolidRectangle(char r, char g, char b, int xPos, int yPos, int width, int height);

	void printText(std::string msg, int xPos, int yPos);

	int getScreenWidth() { return screenWidth; }
	int getScreenHeight() { return screenHeight; }
	int getTileSize() { return tileSize; }

	void makeButton(int xPos, int yPos, int width, int height, bool shown = false);
	int checkButtons(int x, int y);
	void highlightButton(int index, int alpha = 20);
	void hideButtons();
	void clearButtons();

	coords_t center();

	bool checkUpdate() { return needToUpdate; }
	void needUpdate() { needToUpdate = true; }
	void clearUpdate() { needToUpdate = false; }

	void clearScreen();			//not needed, images just replace over the top
	void update();
	void cleanup();

private:

	void setupRenderer(SDL_Renderer* render, int r, int g, int b, int alpha);

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* spritePage;

	SDL_Surface* textSurface;
	SDL_Texture* textTexture;
	SDL_Color fontColor;
	TTF_Font* font;

	SDL_Surface* highlightSurface;
	SDL_Renderer* highlightRenderer;


	Button buttonArray[25];			//max buttons is 25
	int numberOfButtons;

	bool needToUpdate;

	static int screenWidth;
	static int screenHeight;
	static int tileSize;
};

#endif