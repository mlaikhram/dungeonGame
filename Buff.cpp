#include "Buff.h"

Buff::Buff(int id, std::string name, std::string description, int hp, int stamina, int mana, double blockPercent, double manaReduction, int attack, int defense, int unlockLevel) :
	id(id), name(name), description(description), hp(hp), stamina(stamina), mana(mana), blockPercent(blockPercent), manaReduction(manaReduction), attack(attack), defense(defense), unlockLevel(unlockLevel) {}
