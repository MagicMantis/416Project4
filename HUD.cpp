#include "HUD.h"
#include "renderContext.h"

void HUD::update(Uint32 ticks) {
	time -= ticks;
	if (time < 0) time = 0;
}

void HUD::draw() const {
	if (time > 0) {
		SDL_Renderer* rend = RenderContext::getInstance()->getRenderer();
		SDL_Rect dst = {x,y,width,height};
		SDL_SetRenderDrawColor(rend, 155,155,155,100);
		SDL_RenderFillRect(rend,&dst);
		SDL_SetRenderDrawColor(rend, 255,0,155,255);
		SDL_RenderDrawRect(rend,&dst);
	}
}

void HUD::display(int microseconds) {
	time = microseconds;
}