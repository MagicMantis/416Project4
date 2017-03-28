#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "objectManager.h"

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();
  void switchSprite();

private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  World far, back, fore;
  Viewport& viewport;

  // ObjectManager objectManager;
  // std::vector<Drawable*> sprites;

  int currentSprite;
  bool makeVideo;

  void draw() const;
  void update(Uint32);

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
};
