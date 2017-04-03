#include <SDL.h>
#include <SDL2/SDL_ttf.h>

class HUD {
public:
	HUD() : x(0),y(0),width(0),height(0),time(0) { }
	HUD(int xp, int yp, int w, int h) : x(xp), y(yp), 
		width(w), height(h), time(0) { }

	void update(Uint32 ticks);
	void draw() const;
	void display(int);
private:
	int x, y, width, height;
	int time;
};
