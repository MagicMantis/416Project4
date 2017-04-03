#include <cmath>
#include "sprite.h"
#include "gamedata.h"
#include "renderContext.h"

Sprite::Sprite(const std::string& name) :
  Collider(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"), 
                    Gamedata::getInstance().getXmlInt(name+"/speedY")),
            Gamedata::getInstance().getXmlFloat(name+"/width"), 
            Gamedata::getInstance().getXmlFloat(name+"/height")
           ),
  frame( RenderContext::getInstance()->getFrame(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  scale(1.0)
{ }

Sprite::Sprite(const std::string& name, const Vector2f& pos, float s) :
  Collider(name, pos, Vector2f(0,0),
      Gamedata::getInstance().getXmlFloat(name+"/width"), 
      Gamedata::getInstance().getXmlFloat(name+"/height")),
  frame( RenderContext::getInstance()->getFrame(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  scale(s)
{ }

Sprite::Sprite(const Sprite& s) :
  Collider(s), 
  frame(s.frame),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  scale(s.scale)
{ }

Sprite& Sprite::operator=(const Sprite& rhs) {
  Collider::operator=( rhs );
  frame = rhs.frame;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  scale = rhs.scale;
  return *this;
}

void Sprite::draw() const { 
  frame->drawScaled(getX(), getY(), false, scale); 
}

void Sprite::update(Uint32 ticks) { 
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( std::abs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-frameHeight) {
    setVelocityY( -std::abs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( std::abs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-frameWidth) {
    setVelocityX( -std::abs( getVelocityX() ) );
  }  
}
