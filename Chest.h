#ifndef MKL_CHEST
#define MKL_CHEST

#include "Entity.h"

class Chest : public Entity {
public:
	Chest(const char *spriteSheetName, int index, int numx, int numy, Vector3 position, float size = 1.0f);
	void openedBy(Entity &player);
private:
	bool open;
};

#endif MKL_CHEST