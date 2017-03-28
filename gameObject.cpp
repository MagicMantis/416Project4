#include "gameObject.h"

bool GameObject::inBounds(int x, int y, int w, int h) {
	if (x < 0-w || x > WIDTH || y < 0-h || y > HEIGHT) return false;
	return true;
}
