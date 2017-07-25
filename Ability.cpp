#include "Ability.h"

Ability::Ability(int id, std::string name, std::string description, std::string filename, int attack, int speed, int repetitions, int hpCost, int staminaCost, int manaCost, int unlockLevel, int userStance, int victimStance) :
	id(id), name(name), description(description), attack(attack), speed(speed), repetitions(repetitions), hpCost(hpCost), staminaCost(staminaCost), manaCost(manaCost), unlockLevel(unlockLevel), userStance(userStance), victimStance(victimStance), script(filename) {}

Ability::~Ability() {
	script.close();
}