#include "Buff.h"

Buff::Buff(int id, std::string name, std::string description, int hp, int stamina, int mana, int blockPercent, int manaReduction, int attack, int defense, int unlockLevel) :
	id(id), name(name), description(description), hp(hp), stamina(stamina), mana(mana), blockPercent(blockPercent), manaReduction(manaReduction), attack(attack), defense(defense), unlockLevel(unlockLevel) {}

/*void Buff::format(DetailedOption &option) {
	option.setText(name);

	std::string details = "";

	if (hp > 0) details += "hp +" + std::to_string(hp) + " ";
	if (stamina > 0) details += "stamina +" + std::to_string(stamina) + " ";
	if (mana > 0) details += "mana +" + std::to_string(mana) + " ";
	if (attack > 0) details += "attack +" + std::to_string(attack) + " ";
	if (defense > 0) details += "defense +" + std::to_string(defense) + " ";
	if (blockPercent > 0) details += "block +" + std::to_string(blockPercent) + "% ";
	if (manaReduction > 0) details += "mana reduction +" + std::to_string(manaReduction) + "% ";

	details[details.size() - 1] = '.';

	option.setDetails(0, details);
}*/