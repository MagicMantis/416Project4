#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "twoWayMultiSprite.h"
#include "sludge.h"
#include "gamedata.h"
#include "engine.h"
#include "player.h"
#include "frameGenerator.h"

Engine::~Engine() { 
  std::cout << "Terminating program" << std::endl;
  // for (auto& it : sprites) {
  //   delete it;
  // }
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  far("farbuildings", Gamedata::getInstance().getXmlInt("farbuildings/factor") ),
  back("backbuildings", Gamedata::getInstance().getXmlInt("backbuildings/factor") ),
  fore("foreground", Gamedata::getInstance().getXmlInt("foreground/factor") ),
  viewport( Viewport::getInstance() ),
  hud(Gamedata::getInstance().getXmlInt("HUD/x"),
    Gamedata::getInstance().getXmlInt("HUD/y"),
    Gamedata::getInstance().getXmlInt("HUD/width"),
    Gamedata::getInstance().getXmlInt("HUD/height")),
  // sprites(),
  currentSprite(-1),

  makeVideo( Gamedata::getInstance().getXmlBool("makeVideo") )
{
  ObjectManager::getInstance().initObjects();
  //sprites.push_back( new Sludge() );
  switchSprite();
  std::cout << "Loading complete" << std::endl;
  hud.display(3000);
}

void Engine::draw() const {
  far.draw();
  back.draw();
  fore.draw();

  //for(auto* s : sprites) s->draw();
  ObjectManager::getInstance().drawObjects();

  viewport.draw();
  hud.draw(clock.getAvgFps());
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  ObjectManager::getInstance().updateObjects(ticks);
  //for(auto* s : sprites) s->update(ticks);
  far.update();
  back.update();
  fore.update();
  viewport.update(); // always update viewport last
  hud.update(ticks);
}

void Engine::switchSprite(){
  currentSprite++;
  currentSprite = currentSprite % ObjectManager::getInstance().getInstanceCount();
  Viewport::getInstance().setObjectToTrack(ObjectManager::getInstance().getObject(currentSprite));
}

void Engine::play() {
  SDL_Event event;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    while ( SDL_PollEvent(&event) ) {
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if (event.type == SDL_KEYDOWN) {
        switch ( event.key.keysym.sym ) {
          Player* p;
          case SDLK_ESCAPE:
            done = true;
            break;
          case SDLK_q:
            done = true;
            break;
          case SDLK_d:
            Gamedata::getInstance().updateRight(true);
            break;
          case SDLK_a:
            Gamedata::getInstance().updateLeft(true);
            break;
          case SDLK_w:
            p = (Player*) ObjectManager::getInstance().getObject("player");
            p->jump();
            break;
          case SDLK_DOWN:
            p = (Player*) ObjectManager::getInstance().getObject("player");
            p->stop();
            break;
          case SDLK_p:
            if ( clock.isPaused() ) clock.unpause();
            else clock.pause();
            break;
          case SDLK_s:
            clock.toggleSloMo();
            break;
          case SDLK_t:
            switchSprite();
            break;
          case SDLK_F1:
            if (hud.getTime() == 0) hud.display(1000000);
            else hud.display(0);
            break;
          case SDLK_F4:
            if (!makeVideo) {
              std::cout << "Initiating frame capture " << std::endl;
              makeVideo = true;
            } else if (makeVideo) {
              std::cout << "Terminating frame capture " << std::endl;
              makeVideo = false;
            }
            break;
          default:
            break;
        }
        
      }
      if (event.type == SDL_KEYUP) {        
        switch (event.key.keysym.sym) {
          case SDLK_d:
            Gamedata::getInstance().updateRight(false);
            break;
          case SDLK_a:
            Gamedata::getInstance().updateLeft(false);
            break;
          default:
            break;
        }
      }
      if (event.type == SDL_MOUSEMOTION) {
        Gamedata::getInstance().updateMouse(event.motion.x, event.motion.y);
      }
    }

    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
