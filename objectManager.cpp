#include <random>
#include <iostream>
#include <iomanip>
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
  	float u = Gamedata::getInstance().getXmlFloat("sludge/radius"); //Mean size
  	constexpr float d = 0.5f; //Std deviation
	
	std::random_device rd;
	std::mt19937 mt(rd());
	std::normal_distribution<float>dist(u,d);

	for (int i = 0; i < sludgeCount; i++) {
		Vector2f pos;
		pos[0] = Gamedata::getInstance().getRandInRange(-200, 0);
		pos[1] = Gamedata::getInstance().getRandInRange(200, 400);
		addObject( new Sludge(pos, dist(mt)) );
	}
	for (int i = 0; i < sludgeCount; i++) {
		Vector2f pos;
		int width = Gamedata::getInstance().getXmlInt("world/width");
		pos[0] = Gamedata::getInstance().getRandInRange(width, width+200);
		pos[1] = Gamedata::getInstance().getRandInRange(200, 400);
		addObject( new Sludge(pos, dist(mt)) );
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
    Collider* collider = dynamic_cast<Collider*>(obj);
    if (collider) {
    	int x = (int) collider->getX() / gridWidth;
    	int y = (int) collider->getY() / gridHeight;
    	changeGrid(-1,-1,x,y,collider);
    }
}

void ObjectManager::changeGrid(int x1, int y1, int x2, int y2, Collider* collider) {
	if (x1 >= 0 && x1 < gridXs && y1 >= 0 && y1 < gridYs)
		grid[x1*gridYs+y1].remove_if([collider](Collider* c){ return c->getID() == collider->getID();});
	if (x2 >= 0 && x2 < gridXs && y2 >= 0 && y2 < gridYs)
		grid[x2*gridYs+y2].push_back(collider);
}

std::list<Collider*>* ObjectManager::getObjectsInGrid(int x, int y) const {
	if (x < 0 || x >= gridXs || y < 0 || y >= gridYs) return nullptr;
	return &grid[x*gridYs+y];
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

ObjectManager::ObjectManager(int w, int h) : gameObjects(), instanceSets(), 
	gridXs(Gamedata::getInstance().getXmlInt("world/width") / w + 1), 
	gridYs(Gamedata::getInstance().getXmlInt("world/height") / h + 1),
	grid(new std::list<Collider*>[gridXs*gridYs]), gridWidth(w), gridHeight(h) {}