#include "Ability.h"

Ability::Ability(std::string filename, int attack, int speed, int repetitions, int hpCost, int staminaCost, int manaCost, int userStance, int victimStance) :
	attack(attack), speed(speed), repetitions(repetitions), hpCost(hpCost), staminaCost(staminaCost), manaCost(manaCost), userStance(userStance), victimStance(victimStance), script(filename) {}

Ability::~Ability() {
	script.close();
}