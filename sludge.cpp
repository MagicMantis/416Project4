#include "sludge.h"
#include "gamedata.h"
#include "objectManager.h"
#include "viewport.h"
#include <math.h>

Sludge::Sludge() : Sprite("sludge", Vector2f(
	Gamedata::getInstance().getRandInRange(0, 200),
	Gamedata::getInstance().getRandInRange(0, 200)),
	1.0),
	radius(Gamedata::getInstance().getXmlFloat("sludge/radius")),
	player(nullptr),
	gravity(Gamedata::getInstance().getXmlFloat("gravityConstant")),
	damping(Gamedata::getInstance().getXmlFloat("dampingConstant")),
	maxSpeed(Gamedata::getInstance().getXmlFloat("maxSpeed"))
{ }

Sludge::Sludge(const Vector2f& pos, float r) : Sprite("sludge", pos, 
	r/Gamedata::getInstance().getXmlFloat("sludge/radius")),
	radius(r),
	player(nullptr),
	gravity(Gamedata::getInstance().getXmlFloat("gravityConstant")),
	damping(Gamedata::getInstance().getXmlFloat("dampingConstant")),
	maxSpeed(Gamedata::getInstance().getXmlFloat("maxSpeed")) 
{ }

// void Sludge::draw() const {

// }

void Sludge::update(Uint32 ticks) {
	Collider::update(ticks);

	Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
	setPosition(getPosition() + incr);

	//calculate change in velocity this tick
	Vector2f accel;

	//gravity
	float vspeed = getVelocityY();
	if (vspeed < 200.0) accel[1] += gravity;

	//floor bounce
	if (getY()-getFrameHeight()/2 > (Gamedata::getInstance().getXmlInt("world/ground"))) {
		float normalForce = (1.0)*pow((getY()-(getWorldHeight()-100)),2);
		accel[1] -= normalForce/5.0;
		setY(Gamedata::getInstance().getXmlInt("world/ground")+getFrameHeight()/2);
	}

	//bounce off other sludges
	accel = accel + bounce(gravity);

	//seek target
	if (!player) player = (Player *)ObjectManager::getInstance().getObject("player");
	Vector2f target = player->getPosition();
	//target[0] = Gamedata::getInstance().getMouseX() + Viewport::getInstance().getX();
	//target[1] = Gamedata::getInstance().getMouseY() + Viewport::getInstance().getY();
	target[0] += 32;
	target[1] += 32;
	float dist = getDistance(target);
	float xratio = (getX()-target[0]) / dist;
	float yratio = (getY()-target[1]) / dist;
	accel[0] -= Gamedata::getInstance().getXmlFloat("sludge/seekSpeed") * xratio * 2;
	accel[1] -= Gamedata::getInstance().getXmlFloat("sludge/seekSpeed") * yratio;

	//damping
	accel = accel - (damping * getVelocity());

	incr = accel * static_cast<float>(ticks) * .02;
	setVelocity(getVelocity() + incr);
	setVelocityX(Gamedata::clamp(getVelocityX(), -maxSpeed, maxSpeed));
	setVelocityY(Gamedata::clamp(getVelocityY(), -maxSpeed, maxSpeed));
}

//Bounce off other sludges
Vector2f Sludge::bounce(float gravityConstant) {
	Vector2f accel;
	for (int xx = -1; xx <= 1; xx++) {
		for (int yy = -1; yy <= 1; yy++) {
			auto* objs = ObjectManager::getInstance().getObjectsInGrid(getGridX()+xx, getGridY()+yy);
			if (objs) {
				for (Collider* c : *objs) {
					if (c == this) continue;
					Sludge* sludge = dynamic_cast<Sludge*>(c);
					if (sludge) {
						float dist = getDistance(sludge);
						float xratio = (getX()-sludge->getX()) / dist;
						float yratio = (getY()-sludge->getY()) / dist;
						if (dist < radius) {
							float magnitude = gravityConstant / sqrt((radius - dist) / radius);
							accel[0] += xratio * magnitude;
							accel[1] += yratio * magnitude;
						}
					}
				}
			}
		}
	}
	return accel;
}