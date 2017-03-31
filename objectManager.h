#ifndef OBJECTMANAGER__H
#define OBJECTMANAGER__H

#include "drawable.h"
#include "collider.h"
#include <vector>
#include <unordered_map>
#include <list>

/**
 * ObjectManager class: this class contains a vector of all game
 * objects and manages updating and rendering them each frame.
 */
class Collider;
class ObjectManager {
public:
	static ObjectManager& getInstance();
	ObjectManager(const ObjectManager&) = delete;
	ObjectManager& operator=(const ObjectManager&) = delete;
	~ObjectManager();

	void addObject(Drawable*);
	void initObjects(); //generate all objects in the scene
	void updateObjects(Uint32 ticks); //update all objects
	void drawObjects() const; //draw all objects

	int getInstanceCount() const { return gameObjects.size(); }
	Drawable* getObject(int index) const { return gameObjects[index]; }

	Drawable* getObject(const std::string&);
	std::vector<Drawable*>* getObjectsOfType(const std::string&);

	void changeGrid(int, int, int, int);
private:
	ObjectManager(int w, int h) : gameObjects(), instanceSets(), 
		grid(new std::list<Collider>[w*h]), instance_id(0) {}
	std::vector<Drawable*> gameObjects;
	std::unordered_map<std::string, std::vector<Drawable*>*> instanceSets;
	std::list<Collider> *grid;
	int instance_id;
};

#endif