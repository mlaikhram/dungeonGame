#include "Chest.h"

Chest::Chest(const char *spriteSheetName, int index, int numx, int numy, Vector3 position, float size) :
	Entity(spriteSheetName, index, numx, numy, position, size, Vector3(), Vector3(), 0.0f), open(false), openTime(0.0f), opener(nullptr) {}

void Chest::update(ShaderProgram *program, float time) {
	Entity::update(program, time);

	if (open && index == chestc) {
		if (openTime < 0.5f) {
			openTime += time;
			rotation = 0.1 * PI * sin(2 * PI * openTime * 7.0f);
		}
		else {
			rotation = 0.0f;
			endOpen();
		}
	}
}

void Chest::startOpen(Entity &entity) {
	open = true;
	opener = &entity;
}

void Chest::endOpen() {
	index = chesto;
	//give opener all chest items
}