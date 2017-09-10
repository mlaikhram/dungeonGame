#ifndef MKL_ITEM
#define MKL_ITEM

#include <string>
#include <vector>
#include "Util.h"
#include "Bucket.h"

class Item {
public:
	Item(int id, std::string name, std::string description, int type, int hp, int stamina, int mana, int blockPercent, int manaReduction, int attack, int defense, std::vector<Bucket*> buckets, int level = 1, int xp = 0, int sp = 0);

private:
	int id;
	std::string name;
	std::string description;
	int type;
	
	int hp;
	int stamina;
	int mana;

	int blockPercent;
	int manaReduction;

	int attack;
	int defense;

	int level;
	int xp;
	int sp;

	std::vector<Bucket*> buckets;

};

#endif MKL_ITEM