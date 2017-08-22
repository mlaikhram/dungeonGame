#include "Buff.h"

Buff::Buff(int id, std::string name, int hp, int stamina, int mana, int blockPercent, int manaReduction, int attack, int defense, int unlockLevel) :
	id(id), name(name), hp(hp), stamina(stamina), mana(mana), blockPercent(blockPercent), manaReduction(manaReduction), attack(attack), defense(defense), unlockLevel(unlockLevel) {}