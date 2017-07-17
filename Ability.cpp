#include "Ability.h"

Ability::Ability(int id, std::string name, std::string filename, int attack, int speed, int repetitions, int hpCost, int staminaCost, int manaCost, int userStance, int victimStance) :
	id(id), name(name), attack(attack), speed(speed), repetitions(repetitions), hpCost(hpCost), staminaCost(staminaCost), manaCost(manaCost), userStance(userStance), victimStance(victimStance), script(filename) {}

Ability::~Ability() {
	script.close();
}