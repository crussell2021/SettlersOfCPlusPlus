#include "display.h"

int Display::screenWidth = 1280;
int Display::screenHeight = 768;
int Display::tileSize = 128;

Display::Display() {
	window = NULL;				//initialize pointers to NULL
	renderer = NULL;
	spritePage = NULL;
	textSurface = NULL;
	textTexture = NULL;
	font = NULL;
	highlightSurface = NULL;
	highlightRenderer = NULL;

	SDL_Init(SDL_INIT_VIDEO);	//settup SDL for video, and to load png files
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	//create window -- where all the images will be displayed
	window = SDL_CreateWindow("Settlers Of C++", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, 0);

	//create renderer -- loads images onto the window
	renderer = SDL_CreateRenderer(window, -1, 0);
	setupRenderer(renderer, 25, 125, 255, 255);										//clears the screen, and sets up a solid blue background

	//load font for text
	font = TTF_OpenFont("resources/arial.ttf", 16);
	fontColor = { 255, 255, 255, 255 }; //white

	highlightRenderer = SDL_CreateRenderer(window, -1, 0);
	SDL_RenderSetLogicalSize(highlightRenderer, screenWidth, screenHeight);
	setupRenderer(highlightRenderer, 0, 0, 0, 0);

	numberOfButtons = 0;

	needToUpdate = true;
}

void Display::loadSpritePage(std::string fileName) {					//loads image file into spritepage 
	spritePage = IMG_LoadTexture(renderer, fileName.c_str());
}

void Display::setupRenderer(SDL_Renderer* render, int red, int green, int blue, int alpha) {
	SDL_RenderSetLogicalSize(render, screenWidth, screenHeight);		//set size to whole screen
	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(render, red, green, blue, alpha);
	SDL_RenderClear(render);
	SDL_RenderPresent(render);
}

void Display::placeTexture(int xClip, int yClip, int xDst, int yDst, int clipSize, int dstSize) {		//for square images
	SDL_Rect clip, destination;
	clip.x = xClip;
	clip.y = yClip;
	destination.x = xDst;
	destination.y = yDst;
	destination.w = destination.h = dstSize;
	clip.w = clip.h = clipSize;
	SDL_RenderCopy(renderer, spritePage, &clip, &destination);
}


void Display::placeTexture(int xClip, int yClip, int xDst, int yDst, int wClipSize, int hClipSize, int wDstSize, int hDstSize) {
	SDL_Rect clip, destination;
	clip.x = xClip;
	clip.y = yClip;
	destination.x = xDst;
	destination.y = yDst;
	destination.w = wDstSize;
	destination.h = hDstSize;
	clip.w = wClipSize;
	clip.h = hClipSize;
	SDL_RenderCopy(renderer, spritePage, &clip, &destination);
}

void Display::printText(std::string msg, int xPos, int yPos) {
	textSurface = TTF_RenderText_Solid(font, msg.c_str(), fontColor);
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	int textW = 0, textH = 0;
	SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);
	SDL_Rect destination = {xPos, yPos,textW, textH};

	SDL_RenderCopy(renderer, textTexture, NULL, &destination);
}

void Display::placeSolidRectangle(char r, char g, char b, int xPos, int yPos, int width, int height) {
	SDL_Rect box;
	box.x = xPos;
	box.y = yPos;
	box.w = width;
	box.h = height;
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderFillRect(renderer, &box);
}

void Display::update() {
	SDL_RenderPresent(renderer);
	needToUpdate = true;
}

void Display::cleanup() {
	SDL_DestroyTexture(spritePage);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
	SDL_FreeSurface(highlightSurface);
	SDL_DestroyRenderer(highlightRenderer);
	TTF_Quit();
	SDL_Quit();
}

coords_t Display::center() {
	coords_t coords;
	coords.x = getScreenWidth() / 2;
	coords.y = getScreenHeight() / 2;
	return coords;
}

void Display::makeButton(int xPos, int yPos, int width, int height, bool shown) {
	SDL_Rect box = { xPos, yPos, width, height };
	buttonArray[numberOfButtons++] = Button(box, shown);
	if (shown) {
		highlightButton(numberOfButtons - 1, 150);
	}
}

int Display::checkButtons(int x, int y) {
	for (int i = 0; i < numberOfButtons; i++) {
		if (buttonArray[i].checkCoords(x,y)) {
			return i;	//found matching button!
		}
	}
	return -1;	//no matching button found
}

void Display::hideButtons() {
	for (int i = 0; i < numberOfButtons; i++) {
		buttonArray[i].hide();
	}
}

void Display::clearButtons() { 
	hideButtons(); 
	numberOfButtons = 0;
}

void Display::highlightButton(int index, int alpha) {
	SDL_Rect box = buttonArray[index].getBox();
	buttonArray[index].show();
	
	SDL_SetRenderDrawColor(renderer, 0, 110, 20, alpha);
	SDL_RenderFillRect(renderer, &box);
	SDL_RenderPresent(renderer);
}

void Display::clearScreen() {
	SDL_SetRenderDrawColor(renderer, 25, 125, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}