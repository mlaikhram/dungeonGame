#include "Player.h"

Player::Player(int id, std::string name, const char *spriteSheetName, int index, int numx, int numy, Vector3 position, std::vector<int> maxFloor, int **_materials, int coins, float size, Vector3 velocity, Vector3 acceleration, float rotation) :
	Entity(spriteSheetName, index, numx, numy, position, size, velocity, acceleration, rotation), id(id), name(name), maxFloor(maxFloor), coins(coins) {
	materials = new int*[MAX_DUNGEON + 1];
	for (int i = 0; i < MAX_DUNGEON + 1; ++i) {
		materials[i] = new int[MAX_MATERIAL];
	}
	for (int y = 0; y < MAX_DUNGEON + 1; ++y) {
		for (int x = 0; x < MAX_MATERIAL; ++x) {
			materials[y][x] = _materials[y][x];
		}
	}
}

Player::~Player() {
	//cleanup arrays
	for (int i = 0; i < MAX_DUNGEON + 1; ++i) {
		delete materials[i];
	}
	delete materials;
}