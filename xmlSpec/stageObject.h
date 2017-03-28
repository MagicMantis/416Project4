#ifndef STAGEOBJECT_H
#define STAGEOBJECT_H

#include "gameObject.h"
#include "texture.h"

/** 
 * StageObject class: child of gameobject, these objects have
 * a location, size, and texture, and are active only during
 * a single stage of the animation.
 */ 
class StageObject : public GameObject {
public:
	StageObject(int xp, int yp, int w, int h, int ds, Texture* t) : 
			x(xp), y(yp), width(w), height(h), drawStage(ds), doDraw(false), texture(t) {}
	~StageObject() {}

	void update(int stage);
	virtual void draw(SDL_Renderer* render);
protected:
	int x,y,width,height,drawStage; //drawStage says which stage the object is active
	bool doDraw; //should draw during the current frame
	Texture* texture; //texture to draw

	//disallow compiler generated constructors
	StageObject();
	StageObject(const StageObject&);
};

#endif
