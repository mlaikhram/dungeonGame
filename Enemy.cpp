#include "Enemy.h"

Enemy::Enemy(const char *spriteSheetName, int index, int numx, int numy, MoveAI *ai, Entity *target, Vector3 position, float size, Vector3 velocity, Vector3 acceleration, float rotation) : 
	Entity(spriteSheetName, index, numx, numy, position, size, velocity, acceleration, rotation), ai(ai), target(target) {}

void Enemy::update(ShaderProgram *program, float time, DungeonFloor *floor) {
	ai->update(time);
	ai->move(floor, acceleration, position, target->position, 5.0f * TILE_SIZE);

	Entity::update(program, time);
}