#include <random>
#include <iostream>
#include <iomanip>
#include <algorithm>
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

	//generate rain effects
	int rainCount = Gamedata::getInstance().getXmlInt("rain/count");
	float rainSpeed = Gamedata::getInstance().getXmlFloat("rain/speed");
	int w = Gamedata::getInstance().getXmlInt("view/width");
	int h = Gamedata::getInstance().getXmlInt("view/height");
	std::vector<Rain*> rain_vec;
	for (int i = 0; i < rainCount; i++) {
		int len = rand()%4+3;
		Rain* r = new Rain((float)i*((float)w/(float)rainCount), (rand()%h), len, h*(.9)+h*(.1*len/6), rainSpeed);
		rain_vec.push_back(r);
	}
	for (Rain* r : rain_vec) { 
		if (r->getLength() <= 3) addObject(r);
	}

	//generate sludge balls
	int sludgeCount = Gamedata::getInstance().getXmlInt("sludgeCount")/2;
  	float u = Gamedata::getInstance().getXmlFloat("sludge/radius"); //Mean size
  	float d = Gamedata::getInstance().getXmlFloat("sludge/deviation"); //Std deviation
	
	std::random_device rd;
	std::mt19937 mt(rd());
	std::normal_distribution<float>dist(u,d);

	std::vector<Sludge*> tempVec;
	for (int i = 0; i < sludgeCount; i++) {
		Vector2f pos;
		pos[0] = Gamedata::getInstance().getRandInRange(-200, 0);
		pos[1] = Gamedata::getInstance().getRandInRange(200, 400);
		tempVec.push_back( new Sludge(pos, dist(mt)) );
	}
	for (int i = 0; i < sludgeCount; i++) {
		Vector2f pos;
		int width = Gamedata::getInstance().getXmlInt("world/width");
		pos[0] = Gamedata::getInstance().getRandInRange(width, width+200);
		pos[1] = Gamedata::getInstance().getRandInRange(200, 400);
		tempVec.push_back( new Sludge(pos, dist(mt)) );
	}

	sort(tempVec.begin(), tempVec.end(), [](const Sludge* const a, const Sludge* const b) 
		{ return a->getRadius() < b->getRadius(); });
	for (Sludge* s : tempVec) addObject( s );

	//finish effects
	for (Rain* r : rain_vec) { 
		if (r->getLength() > 3) addObject(r);
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