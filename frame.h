#ifndef FRAME__H
#define FRAME__H

#include <iostream>
#include <string>
#include <SDL.h>

class Frame {
public:
  Frame( SDL_Texture*);
  Frame(const Frame&);
  Frame& operator=(const Frame&);

  void draw(int x, int y, bool=false) const;
  void draw(int sx, int sy, int dx, int dy) const;

  SDL_Texture* getTexture() const { return texture; }
  int getWidth()  const { return width; }
  int getHeight() const { return height; }
private:
  SDL_Renderer * renderer;
  SDL_Texture * texture;
  int width;
  int height;
  Frame();
};

#endif
