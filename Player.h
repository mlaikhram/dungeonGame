#ifndef MKL_PLAYER
#define MKL_PLAYER

#include <string>
#include <vector>
#include "Entity.h"
#include "Item.h"

class Player : public Entity {
public:
	Player(int id, std::string name, const char *spriteSheetName, int index, int numx, int numy, Vector3 position, std::vector<int> maxFloor, int **_materials, int coins = 0, float size = 1.0f, Vector3 velocity = Vector3(0, 0, 0), Vector3 acceleration = Vector3(0, 0, 0), float rotation = 0.0f);
	~Player();

private:
	int id;
	std::string name;

	std::vector<Item*> items; //indexed by item slot
	std::vector<int> maxFloor; //indexed by dungeon ([0] is for story flags)
	int **materials; //indexed by dungeon,material# ([0] is for generic items)
	int coins;

	int hp, currentHP;
};

#endif MKL_PLAYER