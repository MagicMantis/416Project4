#include <sstream>
#include "HUD.h"
#include "ioMod.h"
#include "viewport.h"

void HUD::update(Uint32 ticks) {
	time -= ticks;
	if (time < 0) time = 0;
}

void HUD::draw(int fps) const {
	if (time > 0) {
		SDL_Renderer* rend = RenderContext::getInstance()->getRenderer();
		SDL_Rect dst = {x,y,width,height};
		SDL_SetRenderDrawBlendMode(rend,SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(rend, 155,155,155,100);
		SDL_RenderFillRect(rend,&dst);
		SDL_SetRenderDrawColor(rend, 100,100,100,255);
		SDL_RenderDrawRect(rend,&dst);

  		IOmod& io = IOmod::getInstance();
  		io.writeText("Tracking: "+Viewport::getInstance().getObjectToTrack()->getName(), 30, 30);

		std::stringstream strm;
		strm << "Average FPS: " << fps;
		io.writeText(strm.str(), 30, 60);
	}
}

void HUD::display(int microseconds) {
	time = microseconds;
}