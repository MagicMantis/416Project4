#include "stageObject.h"
#include <cstdlib>

void StageObject::update(int stage) {
	doDraw = (stage == drawStage);
	if (doDraw) {
		x += rand()%3-1;
		y += rand()%3-1;	
	}
}

void StageObject::draw(SDL_Renderer* render) {
	if (doDraw) {
		SDL_Rect dstrect = {x, y, texture->getWidth(), texture->getHeight()};
		SDL_RenderCopy(render, texture->getImage(), NULL, &dstrect);
	}
}
