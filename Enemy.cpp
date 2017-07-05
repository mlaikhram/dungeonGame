#include "Enemy.h"

Enemy::Enemy(const char *spriteSheetName, int index, int numx, int numy, MoveAI *ai, Entity *target, Vector3 position, float size, Vector3 velocity, Vector3 acceleration, float rotation) : 
	Entity(spriteSheetName, index, numx, numy, position, size, velocity, acceleration, rotation), ai(ai), target(target) {}

Enemy::Enemy(const Enemy &e) : Enemy("none", e.index, e.numx, e.numy, e.ai->clone(), e.target, e.position, e.size, e.velocity, e.acceleration, e.rotation) {
	spriteSheet = e.spriteSheet;
}

Enemy::~Enemy() {
	delete ai;
}

void Enemy::update(ShaderProgram *program, float time, DungeonFloor *floor) {
	ai->update(time);

	float offset = (TILE_SIZE) / 2;

	Vector3 positionf(position.x + offset, position.y - offset, position.z);
	Vector3 target_positionf(target->position.x + offset, target->position.y - offset, target->position.z);
	ai->move(floor, acceleration, positionf, target_positionf, 5.0f * TILE_SIZE);

	//ai->move(floor, acceleration, position, target->position, 5.0f * TILE_SIZE);

	Entity::update(program, time);
}