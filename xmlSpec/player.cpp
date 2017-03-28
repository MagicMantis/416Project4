#include "player.h"
#include "gamedata.h"

Player::Player(const std::string& name) : TwoWayMultiSprite(name) 
{ }

Player::Player(const Player& p) : TwoWayMultiSprite(p.getName())
{ }

// helper function
float clamp(float val, float low, float high) {
  if (val < low) val = low; 
  if (val > high) val = high;
  return val;
}

void Player::update(Uint32 ticks) {
	if (getVelocityX() != 0) TwoWayMultiSprite::update(ticks);
	Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
	setPosition(getPosition() + incr);

	//gravity
	if (!onGround()) {
		float gravity = Gamedata::getInstance().getXmlFloat("gravityConstant");
		setVelocityY(getVelocityY() + gravity);
	}

	//acceleration
	float accel = Gamedata::getInstance().getXmlFloat("player/acceleration");
	if (Gamedata::getInstance().getRightKey()) accelerate(accel);
	else if (getVelocityX() > 0) decelerate(accel);
	if (Gamedata::getInstance().getLeftKey()) accelerate(-accel);
	else if (getVelocityX() < 0) decelerate(accel);
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
	if (abs(getVelocityX()) < amount) setVelocityX(0);
	else setVelocityX(getVelocityX() + (amount * sign));
}

void Player::jump() {
	if (!onGround()) return;
	float jumpPower = Gamedata::getInstance().getXmlFloat("player/jumpPower");
	setVelocityY(getVelocityY() - jumpPower);
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