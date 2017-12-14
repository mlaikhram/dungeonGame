#ifndef MKL_ENEMY
#define MKL_ENEMY

#include "Entity.h"
#include "MoveAI.h"
#include "DungeonFloor.h"

class MoveAI;

class Enemy : public Entity {
public:
	Enemy(const char *spriteSheetName, int index, int numx, int numy, MoveAI *ai, Entity *target, Vector3 position, float size = 1.0f, Vector3 velocity = Vector3(0, 0, 0), Vector3 acceleration = Vector3(0, 0, 0), float rotation = 0.0f);
	Enemy(const Enemy &enemy);
	~Enemy();
	//MUST IMPLEMENT MOVE CONSTRUCTOR TO FIX AI ISSUE
	void update(ShaderProgram *program, float time, DungeonFloor *floor);

private:
	MoveAI *ai;
	Entity *target; //shallow
};

#endif MKL_ENEMY