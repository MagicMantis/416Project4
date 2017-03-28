#include <cmath>
#include "sprite.h"
#include "gamedata.h"
#include "renderContext.h"

Sprite::Sprite(const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"), 
                    Gamedata::getInstance().getXmlInt(name+"/speedY")) 
           ),
  frame( RenderContext::getInstance()->getFrame(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight())
{ }

Sprite::Sprite(const std::string& name, const Vector2f& pos) :
  Drawable(name, pos, Vector2f(0,0)),
  frame( RenderContext::getInstance()->getFrame(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight())
{ }

Sprite::Sprite(const Sprite& s) :
  Drawable(s), 
  frame(s.frame),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight())
{ }

Sprite& Sprite::operator=(const Sprite& rhs) {
  Drawable::operator=( rhs );
  frame = rhs.frame;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  return *this;
}

void Sprite::draw() const { 
  frame->draw(getX(), getY()); 
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

float Sprite::getDistance(const Sprite* s) const {
  return sqrt(pow(getX()-s->getX(), 2) + pow(getY()-s->getY(), 2));
}

float Sprite::getDistance(const Vector2f& v) const {
  return sqrt(pow(getX()-v[0], 2) + pow(getY()-v[1], 2));
}
