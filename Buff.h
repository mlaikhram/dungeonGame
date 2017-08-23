#ifndef MKL_BUFF
#define MKL_BUFF

#include <string>

class Buff {
public:
	Buff(int id, std::string name, int hp, int stamina, int mana, int blockPercent, int manaReduction, int attack, int defense, int unlockLevel, int unlockSP);

	bool operator<(const Buff &rhs) const;

	int id;
	std::string name;

	int hp;
	int stamina;
	int mana;

	int blockPercent;
	int manaReduction;

	int attack;
	int defense;

	int unlockLevel;
	int unlockSP;

};

#endif MKL_BUFF