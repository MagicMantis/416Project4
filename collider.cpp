#include "collider.h"
#include "objectManager.h"

void Collider::update(Uint32 ticks) {
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
