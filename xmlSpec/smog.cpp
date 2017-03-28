#include "smog.h"
#include "gamedata.h"
#include "objectManager.h"
#include "viewport.h"
#include <math.h>

Smog::Smog() : MultiSprite("smog") { 
	Vector2f pos;
	pos[0] = Gamedata::getInstance().getRandInRange(0, Gamedata::getInstance().getXmlInt("world/width"));
	pos[1] = Gamedata::getInstance().getRandInRange(0, Gamedata::getInstance().getXmlInt("world/height")/2);
	setPosition(pos);
	//setVelocityX(10.0);
}

void Smog::update(Uint32 ticks) {
	advanceFrame(ticks);
	Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
	setPosition(getPosition() + incr);

	if (getPosition()[0] > Gamedata::getInstance().getXmlInt("world/width")) {
		Vector2f pos = getPosition();
		pos[0] = -100;
		setPosition(pos);
	}
}