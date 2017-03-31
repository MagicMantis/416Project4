#include "drawable.h"
#include "gamedata.h"

class Collider : public Drawable {
public:
	Collider(const std::string& n, const Vector2f& pos, 
			const Vector2f& vel, float w, float h): 
    	Drawable(n,pos,vel), width(w), height(h), 
    	gridX(pos[0]/Gamedata::getInstance().getXmlInt("grid/width")),
    	gridY(pos[0]/Gamedata::getInstance().getXmlInt("grid/height")),
    	id(Gamedata::getInstance().generateId()) { }

	Collider(const Collider& s) : Drawable(s), width(s.width), height(s.height),
		gridX(s.gridX), gridY(s.gridY), id(s.id) { }

	float getWidth() const { return width; }
	float getHeight() const { return width; }

	virtual void draw() const = 0;
	virtual void update(Uint32 ticks) = 0;
	virtual const Frame* getFrame() const = 0;
private:
	float width, height;
	int gridX, gridY;
	int id;
};
