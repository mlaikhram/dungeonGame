#ifndef MKL_ITEM
#define MKL_ITEM

#include <string>
#include <vector>
#include "Util.h"
#include "Buff.h"
#include "Bucket.h"

class Item {
public:
	Item(int id, std::string name, std::string description, std::string type, Buff baseStats, std::vector<Bucket*> buckets, int level = 1, int xp = 0, int sp = 0);

private:
	int id;
	std::string name;
	std::string description;
	std::string type;
	Buff baseStats;

	int level;
	int xp;
	int sp;

	std::vector<Bucket*> buckets;

};

#endif MKL_ITEM