#include "button.h"

Button::Button() {
	box = { 0,0,0,0 };
	isShown = false;
}

Button::Button(SDL_Rect box, bool show) {
	this->box = box;
	isShown = show;
}

Button::Button(int x, int y, int w, int h, bool show) {
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
	isShown = show;
}

bool Button::checkX(int val) {
	if (val < box.x + box.w && val > box.x) {		//if val within box x
		return true;
	}
	return false;
}

bool Button::checkY(int val) {
	if (val < box.y + box.h && val > box.y) {		//if val within box x
		return true;
	}
	return false;
}

bool Button::checkCoords(int x, int y) {
	if (checkX(x) && checkY(y)) {
		return true;
	}
	return false;
}