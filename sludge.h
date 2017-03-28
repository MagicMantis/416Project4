#include "sprite.h"

class Sludge : public Sprite {
public:
	Sludge();
	Sludge(const Vector2f&);
	~Sludge() { }

	// void draw() const;
	void update(Uint32 ticks);
private:
	float radius;
};
