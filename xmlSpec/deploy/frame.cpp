#include "drawable.h"
#include "frame.h"
#include "ioMod.h"
#include "viewport.h"
#include "renderContext.h"

Frame::Frame( SDL_Texture* tex ) : 
  renderer(RenderContext::getInstance()->getRenderer()),
  texture( tex ),
  width(0), 
  height(0)
{ SDL_QueryTexture(texture, NULL, NULL, &width, &height); }

Frame::Frame( const Frame& frame ) :
  renderer(frame.renderer),
  texture(frame.texture), 
  width(frame.width), 
  height(frame.height)
{ }


Frame& Frame::operator=(const Frame& rhs) {
  renderer = rhs.renderer;
  texture = rhs.texture;
  width = rhs.width;
  height = rhs.height;
  return *this;
}

void Frame::draw(int x, int y, bool doFlip) const {
  x -= Viewport::getInstance().getX();
  y -= Viewport::getInstance().getY();
  SDL_Rect dest = {x, y, width, height };
  SDL_RendererFlip flip = (doFlip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
  SDL_RenderCopyEx(renderer, texture, NULL, &dest, 0, NULL, flip);
}

void Frame::draw(int sx, int sy, int dx, int dy) const {
  SDL_Rect src = { sx, sy, width, height };    
  SDL_Rect dst = { dx, dy, width, height };
  SDL_RenderCopy(renderer, texture, &src, &dst);
}

