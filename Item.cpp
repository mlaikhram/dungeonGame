#include "Item.h"

Item::Item(int id, std::string name, std::string description, std::string type, Buff baseStats, std::vector<Bucket*> buckets, int level, int xp, int sp) : 
	id(id), name(name), description(description), type(type), baseStats(baseStats), buckets(buckets), level(level), xp(xp), sp(sp) {}