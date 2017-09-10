#ifndef MKL_PLAYERCOMBAT
#define MKL_PLAYERCOMBAT

#include <vector>
#include <set>
#include "Passive.h"
#include "Ability.h"
#include "Player.h"

class PlayerCombat {
public:
	PlayerCombat(Player &player);

private:
	int hp, maxHP;
	int stamina, maxStamina;
	int mana, maxMana;

	int blockPercent;
	int manaReduction;

	int attack;
	int defense;

	std::vector<std::set<Passive*>> passives; //indexed by timing
	std::set<Ability*> abilities;
};

#endif MKL_PLAYERCOMBAT