#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include "frameGenerator.h"

/**
 * GameObject class: this represents an entity in the game.
 * All game objects must be drawable and have an update function.
 */ 
class GameObject {
public:
	virtual ~GameObject() {}
	virtual void update(int stage)=0; //update function takes current animation stage as param
	virtual void draw(SDL_Renderer* render)=0; //draw obj to specified renderer

	bool inBounds(int x, int y, int w, int h); //check if in the screen (for drawing)
};

#endif
