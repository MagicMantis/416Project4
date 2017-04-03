#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include "renderContext.h"

class HUD {
public:
	HUD() : renderer(RenderContext::getInstance()->getRenderer()),
		x(0),y(0),width(0),height(0),time(0) { }
	HUD(int xp, int yp, int w, int h) : 
		renderer(RenderContext::getInstance()->getRenderer()),
		x(xp), y(yp), width(w), height(h), time(0) { }

	int getTime() const { return time; }

	void update(Uint32 ticks);
	void draw(int) const;
	void display(int);
private:
	SDL_Renderer * renderer;
	int x, y, width, height;
	int time;
};
