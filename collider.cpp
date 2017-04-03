#include "collider.h"
#include "objectManager.h"

void Collider::update(Uint32 ticks) {
	if (ticks == 0) return;
	int newGridX = gridX, newGridY = gridY;
	if (getX() >= (gridX+1)*Gamedata::getInstance().getXmlInt("grid/width")) {
		newGridX = gridX+1;
	}
	else if (getX() < gridX*Gamedata::getInstance().getXmlInt("grid/width")) {
		newGridX = gridX-1;
	}
	if (getY() >= (gridY+1)*Gamedata::getInstance().getXmlInt("grid/height")) {
		newGridY = gridY+1;
	}
	else if (getY() < gridY*Gamedata::getInstance().getXmlInt("grid/height")) {
		newGridY = gridY-1;
	}
	if (gridX != newGridX || gridY != newGridY) {
		ObjectManager::getInstance().changeGrid(gridX,gridY,newGridX,newGridY,this);
		gridX = newGridX;
		gridY = newGridY;
	}
}

float Collider::getDistance(const Collider* s) const {
  return sqrt(pow(getX()-s->getX(), 2) + pow(getY()-s->getY(), 2));
}

float Collider::getDistance(const Vector2f& v) const {
  return sqrt(pow(getX()-v[0], 2) + pow(getY()-v[1], 2));
}