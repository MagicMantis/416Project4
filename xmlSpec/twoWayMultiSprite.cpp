#include "twoWayMultiSprite.h"
#include "gamedata.h"
#include "renderContext.h"

TwoWayMultiSprite::TwoWayMultiSprite( const std::string& name) :
  MultiSprite(name), facingRight(true) { }

TwoWayMultiSprite::TwoWayMultiSprite(const TwoWayMultiSprite& s) :
  MultiSprite(s), facingRight(s.facingRight) { }

void TwoWayMultiSprite::draw() const { 
  frames[currentFrame]->draw(getX(), getY(), !facingRight);
}

void TwoWayMultiSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);
  facingRight = (getVelocityX() >= 0);
}
