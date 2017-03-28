#include "objectManager.h"
#include "sludge.h"
#include "smog.h"
#include "player.h"
#include "gamedata.h"

ObjectManager& ObjectManager::getInstance() {
  static ObjectManager objectManager;
  return objectManager;
}

void ObjectManager::initObjects() {
	addObject( new Player("player") );
	int sludgeCount = Gamedata::getInstance().getXmlInt("sludgeCount")/2;
	for (int i = 0; i < sludgeCount; i++) {
		Vector2f pos;
		pos[0] = Gamedata::getInstance().getRandInRange(-200, 0);
		pos[1] = Gamedata::getInstance().getRandInRange(200, 400);
		addObject( new Sludge(pos) );
	}
	for (int i = 0; i < sludgeCount; i++) {
		Vector2f pos;
		int width = Gamedata::getInstance().getXmlInt("world/width");
		pos[0] = Gamedata::getInstance().getRandInRange(width, width+200);
		pos[1] = Gamedata::getInstance().getRandInRange(200, 400);
		addObject( new Sludge(pos) );
	}
	for (int i = 0; i < 20; i++) {
		addObject( new Smog() );
	}
}

void ObjectManager::addObject(Drawable* obj) {
	gameObjects.push_back(obj);
	auto search = instanceSets.find(obj->getName());
    if(search != instanceSets.end()) {
        search->second->push_back(obj);
    }
    else {
        instanceSets[obj->getName()] = new std::vector<Drawable*>();
        instanceSets[obj->getName()]->push_back(obj);
    }
}

//update all game objects
void ObjectManager::updateObjects(Uint32 ticks) {
	for ( size_t i = 0; i < gameObjects.size(); i++ ) {
		gameObjects[i]->update(ticks);
	}
}

//draw all objects
void ObjectManager::drawObjects() const {
	for ( size_t   i = 0; i < gameObjects.size(); i++ ) {
		gameObjects[i]->draw();
	}
}

ObjectManager::~ObjectManager() {
	for (auto& it : gameObjects) delete it;
	for (auto& it : instanceSets) delete it.second;
}

Drawable* ObjectManager::getObject(const std::string& type) {
	return (*instanceSets[type])[0];
}

std::vector<Drawable*>* ObjectManager::getObjectsOfType(const std::string& type) {
	return instanceSets[type];
}
