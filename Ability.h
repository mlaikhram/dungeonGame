#ifndef MKL_ABILITY
#define MKL_ABILITY

#include <fstream>

class Ability {
public:
	Ability(int id, std::string name, std::string description, std::string filename, int attack, int speed, int repetitions, int hpCost, int staminaCost, int manaCost, int unlockLevel, int unlockSP, int userStance = -1, int victimStance = -1);
	
	bool operator<(const Ability &rhs) const;

	~Ability();

	int id;
	std::string name;
	std::string description;

	std::ifstream script;

	int attack;
	int speed;
	int repetitions;

	//negative cost for restoration
	int hpCost;
	int staminaCost;
	int manaCost;
	
	int unlockLevel;
	int unlockSP;

	//what stance to put the respective entity in after the ability is used (-1 if no stance change)
	int userStance;
	int victimStance;


};

#endif MKL_ABILITY