#include "Item.h"

Item::Item(int id, std::string name, std::string description, int type, int hp, int stamina, int mana, int blockPercent, int manaReduction, int attack, int defense, std::vector<Bucket*> buckets, int level, int xp, int sp) :
	id(id), name(name), description(description), type(type), hp(hp), stamina(stamina), mana(mana), blockPercent(blockPercent), manaReduction(manaReduction), attack(attack), defense(defense), buckets(buckets), level(level), xp(xp), sp(sp) {}