#ifndef MKL_CHEST
#define MKL_CHEST

#include "Entity.h"

class Chest : public Entity {
public:
	Chest(const char *spriteSheetName, int index, int numx, int numy, Vector3 position, float size = 1.0f);
	void update(ShaderProgram *program, float time);
	void startOpen(Entity &opener);
	void endOpen();
private:
	bool open;
	float openTime;
	Entity *opener; //shallow
};

#endif MKL_CHEST