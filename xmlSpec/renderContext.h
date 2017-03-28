#include <iostream>
#include <SDL.h>
#include "frameFactory.h"

class RenderContext{
public:
  static RenderContext* getInstance();
  ~RenderContext();
  SDL_Window* getWindow() const { return window; }
  SDL_Renderer* getRenderer() const { return renderer; }

  Frame* getFrame(const std::string& n) { 
    return FrameFactory::getInstance()->getFrame(n);
  }
  std::vector<Frame*> getFrames(const std::string& n) {
    return FrameFactory::getInstance()->getFrames(n);
  }
private:
  static RenderContext* instance;
  SDL_Window* window;
  SDL_Renderer* renderer;

  FrameFactory factory;

  SDL_Window* initWindow();
  SDL_Renderer* initRenderer();
  RenderContext();
  RenderContext(const RenderContext&) = delete;
  RenderContext& operator=(const RenderContext&) = delete;
};
