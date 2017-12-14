#include "Enemy.h"
std::ofstream ofs("output.txt");

Enemy::Enemy(const char *spriteSheetName, int index, int numx, int numy, MoveAI *ai, Entity *target, Vector3 position, float size, Vector3 velocity, Vector3 acceleration, float rotation) : 
	Entity(spriteSheetName, index, numx, numy, position, size, velocity, acceleration, rotation), ai(ai), target(target) {
	ofs << "constructed" << std::endl;
}

Enemy::Enemy(const Enemy &e) : Enemy("none", e.index, e.numx, e.numy, e.ai->clone(), e.target, e.position, e.size, e.velocity, e.acceleration, e.rotation) {
	ofs << "copied" << std::endl;
	spriteSheet = e.spriteSheet;
}

Enemy::~Enemy() {
	if (ai != nullptr) {
		ofs << "deleting ai" << std::endl;
	}
	else {
		ofs << "safe delete of ai" << std::endl;
	}
	delete ai;
}
Enemy::Enemy(Enemy &&e) : ai(nullptr), target(nullptr), Entity("none", 0, 0, 0, Vector3()) {
	ofs << "moved" << std::endl;
	spriteSheet = e.spriteSheet;
	index = e.index;
	numx = e.numx;
	numy = e.numy;
	position = e.position;
	size = e.size;
	velocity = e.velocity;
	acceleration = e.acceleration;
	rotation = e.rotation;
	ai = e.ai;
	target = e.target;

	e.ai = nullptr;
	e.target = nullptr;
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

MoveAI* Enemy::getAI() const {
	return ai;
}