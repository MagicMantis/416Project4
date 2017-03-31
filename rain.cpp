#include <iostream>
#include "rain.h"

void Rain::update(Uint32 ticks) {
	Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
	setPosition(getPosition() + incr);

	if (getY() > wrap) setY(-length);
	if (getX() < 0) setX(Gamedata::getInstance().getXmlInt("view/width"));
}

void Rain::draw() const {
	SDL_Renderer* render = RenderContext::getInstance()->getRenderer();
	SDL_RenderSetScale(render, (float)length/10.0f+.5, (float)length/10.0f+.5);
	SDL_SetRenderDrawColor(render, 0x88,0x88,0xcc,0xff);
	SDL_RenderDrawLine(render, getX(),getY(),getX(),getY()+length);
	SDL_RenderSetScale(render, 1,1);
}

Rain::~Rain() {
	
}
