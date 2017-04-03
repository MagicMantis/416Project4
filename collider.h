#ifndef COLLIDER_H
#define COLLIDER_H

#include "drawable.h"
#include "gamedata.h"

class Collider : public Drawable {
public:
	Collider(const std::string& n, const Vector2f& pos, 
			const Vector2f& vel, float w, float h): 
    	Drawable(n,pos,vel), width(w), height(h), 
    	gridX(pos[0]/Gamedata::getInstance().getXmlInt("grid/width")),
    	gridY(pos[1]/Gamedata::getInstance().getXmlInt("grid/height")),
    	id(Gamedata::getInstance().generateID()) { }

	Collider(const Collider& s) : Drawable(s), width(s.width), height(s.height),
		gridX(s.gridX), gridY(s.gridY), id(s.id) { }

	float getWidth() const { return width; }
	void setWidth(float w) { width = w; }
	float getHeight() const { return width; }
	void setHeight(float h) { height = h; }

	float getGridX() const { return gridX; }
	void setGridX(float x) { gridX = x; }
	float getGridY() const { return gridY; }
	void setGridY(float y) { gridY = y; }

  	float getDistance(const Collider*) const;
  	float getDistance(const Vector2f&) const;

	int getID() const { return id; }

	virtual void draw() const = 0;
	virtual void update(Uint32 ticks);
	virtual const Frame* getFrame() const = 0;
private:
	float width, height;
	int gridX, gridY;
	int id;
};

#endif
