#include "objectManager.h"
#include "sludge.h"
#include "smog.h"
#include "player.h"
#include "rain.h"
#include "gamedata.h"

ObjectManager& ObjectManager::getInstance() {
  int gridWidth = Gamedata::getInstance().getXmlInt("grid/width");
  int gridHeight = Gamedata::getInstance().getXmlInt("grid/height");
  static ObjectManager objectManager(gridWidth, gridHeight);
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
	int rainCount = Gamedata::getInstance().getXmlInt("rain/count");
	float rainSpeed = Gamedata::getInstance().getXmlFloat("rain/speed");
	int w = Gamedata::getInstance().getXmlInt("view/width");
	int h = Gamedata::getInstance().getXmlInt("view/height");
	for (int i = 0; i < rainCount; i++) {
		addObject(new Rain(i*(w/rainCount), (rand()%h), rand()%3+3, h, rainSpeed));
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