#include "Chest.h"

Chest::Chest(const char *spriteSheetName, int index, int numx, int numy, Vector3 position, float size) :
	Entity(spriteSheetName, index, numx, numy, position, size, Vector3(), Vector3(), 0.0f), open(false) {}

void Chest::openedBy(Entity &player) {

}