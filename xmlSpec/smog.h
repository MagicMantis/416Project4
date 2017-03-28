#include "multisprite.h"

class Smog : public MultiSprite {
public:
	Smog();
	~Smog() { }

	// void draw() const;
	void update(Uint32 ticks);
private:
};
