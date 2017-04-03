#include "player.h"
#include "gamedata.h"
#include "viewport.h"
#include "objectManager.h"
#include "sludge.h"

Player::Player(const std::string& name) : TwoWayMultiSprite(name), fear(0.0) 
{ }

Player::Player(const Player& p) : TwoWayMultiSprite(p.getName()), fear(0.0)
{ }

// helper function
float clamp(float val, float low, float high) {
  if (val < low) val = low; 
  if (val > high) val = high;
  return val;
}

void Player::update(Uint32 ticks) {
	Collider::update(ticks);

	if (getVelocityX() != 0) TwoWayMultiSprite::update(ticks);
	Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
	setPosition(getPosition() + incr);

	//gravity
	if (!onGround()) {
		float gravity = Gamedata::getInstance().getXmlFloat("gravityConstant") 
			* static_cast<float>(ticks) * 0.04;
		setVelocityY(getVelocityY() + gravity);
	}

	//acceleration
	float accel = Gamedata::getInstance().getXmlFloat("player/acceleration")
		* static_cast<float>(ticks) * 0.04;
	float decel = Gamedata::getInstance().getXmlFloat("player/deceleration")
		* static_cast<float>(ticks) * 0.04;
	if (Gamedata::getInstance().getRightKey()) accelerate(accel);
	else if (getVelocityX() > 0) decelerate(decel);
	if (Gamedata::getInstance().getLeftKey()) accelerate(-accel);
	else if (getVelocityX() < 0) decelerate(decel);

	//cause screen jitter from fear
	for (int xx = -1; xx <= 1; xx++) {
		for (int yy = -1; yy <= 1; yy++) {
			auto* objs = ObjectManager::getInstance().getObjectsInGrid(getGridX()+xx, getGridY()+yy);
			if (objs) {
				for (Collider* c : *objs) {
					if (c == this) continue;
					Sludge* sludge = dynamic_cast<Sludge*>(c);
					if (sludge) {
						float dist = getDistance(sludge);
						if (dist < sludge->getRadius()*3) {
							fear += 0.1;
						}
					}
				}
			}
		}
	}
	fear -= 0.001;
	fear = Gamedata::clamp(fear, 0.0, 3.0);
	Viewport::getInstance().setJitter(fear);
}

void Player::draw() const {
	TwoWayMultiSprite::draw();
}

void Player::accelerate(float amount) {
	setVelocityX(getVelocityX() + amount);
	float maxSpeed = Gamedata::getInstance().getXmlFloat("player/maxSpeed");
	setVelocityX(Gamedata::clamp(getVelocityX(), -maxSpeed, maxSpeed));
}

void Player::decelerate(float amount) {
	float sign = (getVelocityX() >= 0 ? -1.0 : 1.0);
	if (abs(getVelocityX()) < amount) {
		currentFrame = 0;
		setVelocityX(0.0);
	}
	else setVelocityX(getVelocityX() + (amount * sign));
}

void Player::jump() {
	if (!onGround()) return;
	float jumpPower = Gamedata::getInstance().getXmlFloat("player/jumpPower");
	setVelocityY(-jumpPower);
}

void Player::stop() {
	Vector2f stopSpeed;
	setVelocity(stopSpeed);
}

bool Player::onGround() {
	float groundLocation = Gamedata::getInstance().getXmlFloat("world/ground");
	if (getY()+frameHeight/2 > groundLocation) {
		setVelocityY(0);
		setY(groundLocation-frameHeight/2);
	}
	if (getY()+frameHeight/2 == groundLocation) return true;
	return false;
}