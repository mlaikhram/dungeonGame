#include "Enemy.h"

Enemy::Enemy(const char *spriteSheetName, int index, int numx, int numy, MoveAI *ai, Entity *target, Vector3 position, float size, Vector3 velocity, Vector3 acceleration, float rotation) : 
	Entity(spriteSheetName, index, numx, numy, position, size, velocity, acceleration, rotation), ai(ai) {}

void Enemy::update(ShaderProgram *program, float time) {
	ai->update(time);
	ai->move(acceleration, position, target->position, false, 0);

	Entity::update(program, time);
}