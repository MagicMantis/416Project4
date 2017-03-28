#include "drawable.h"
#include <vector>
#include <unordered_map>

/**
 * ObjectManager class: this class contains a vector of all game
 * objects and manages updating and rendering them each frame.
 */
class ObjectManager {
public:
	static ObjectManager& getInstance();
	~ObjectManager();

	void addObject(Drawable*);
	void initObjects(); //generate all objects in the scene
	void updateObjects(Uint32 ticks); //update all objects
	void drawObjects() const; //draw all objects

	int getInstanceCount() const { return gameObjects.size(); }
	Drawable* getObject(int index) const { return gameObjects[index]; }

	Drawable* getObject(const std::string&);
	std::vector<Drawable*>* getObjectsOfType(const std::string&);
private:
	ObjectManager() : gameObjects(), instanceSets() {}
	std::vector<Drawable*> gameObjects;
	std::unordered_map<std::string, std::vector<Drawable*>*> instanceSets;
};
