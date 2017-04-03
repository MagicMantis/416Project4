#include "sprite.h"
#include "player.h"

class Sludge : public Sprite {
public:
	Sludge();
	Sludge(const Vector2f&, float);
	Sludge(const Sludge&) = delete;
	Sludge& operator=(const Sludge&) = delete;
	~Sludge() { }

	float getRadius() const { return radius; }

	// void draw() const;
	void update(Uint32 ticks);
private:
	float radius;
	Player* player;
	float gravity, damping, maxSpeed;

	Vector2f bounce(float);
};
