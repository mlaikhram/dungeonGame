#ifndef MKL_BUFF
#define MKL_BUFF

#include <string>

class Buff {
public:
	Buff(int id, std::string name, std::string description, int hp, int stamina, int mana, double blockPercent, double manaReduction, int attack, int defense, int unlockLevel);

	int id;
	std::string name;
	std::string description;

	int hp;
	int stamina;
	int mana;

	double blockPercent;
	double manaReduction;

	int attack;
	int defense;

	int unlockLevel;

};

#endif MKL_BUFF