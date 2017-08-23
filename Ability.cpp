#include "Ability.h"

Ability::Ability(int id, std::string name, std::string description, std::string filename, int attack, int speed, int repetitions, int hpCost, int staminaCost, int manaCost, int unlockLevel, int unlockSP, int userStance, int victimStance) :
	id(id), name(name), description(description), attack(attack), speed(speed), repetitions(repetitions), hpCost(hpCost), staminaCost(staminaCost), manaCost(manaCost), unlockLevel(unlockLevel), unlockSP(unlockSP), userStance(userStance), victimStance(victimStance), script(filename) {}

bool Ability::operator<(const Ability &rhs) const {
	return unlockSP < rhs.unlockSP;
}


Ability::~Ability() {
	script.close();
}