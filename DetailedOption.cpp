#include "Util.h"
#include "DetailedOption.h"

DetailedOption::DetailedOption(std::string phrase, Vector3 position, std::string detail, Vector3 detailPos, const char *spriteSheetName, int numx, int numy, float tileSize, int alignment, int detailedAlign, float spacing) :
	MenuOption(phrase, position, spriteSheetName, numx, numy, tileSize, tileSize, alignment, spacing), details(), displayDetails(false) {
	details.push_back(Text(detail, detailPos, spriteSheetName, numx, numy, tileSize, detailedAlign, spacing));
}

DetailedOption::DetailedOption(std::string phrase, Vector3 position, std::vector<std::string> detailList, Vector3 detailPos, const char *spriteSheetName, int numx, int numy, float tileSize, int alignment, int detailedAlign, float spacing) :
	MenuOption(phrase, position, spriteSheetName, numx, numy, tileSize, tileSize, alignment, spacing), details(), displayDetails(false) {
	for (int i = 0; i < detailList.size(); ++i) 
		details.push_back(Text(detailList[i], Vector3(detailPos.x, detailPos.y + (tileSize - spacing) * i, detailPos.z), spriteSheetName, numx, numy, tileSize, detailedAlign, spacing));
}

DetailedOption::DetailedOption(Buff &buff, Vector3 position, const char *spriteSheetName, int numx, int numy, float tileSize, int alignment, float spacing) : 
	MenuOption(buff.name, position, spriteSheetName, numx, numy, tileSize, tileSize, alignment, spacing), details(), displayDetails(false) {
	int lineNum = 0;
	float x = position.x + ((1 - alignment / 2.0) * 20) * (tileSize * (1 - spacing)) + tileSize;
	if (buff.hp > 0) details.push_back(Text("hp +" + std::to_string(buff.hp), Vector3(x, position.y - (lineNum++ * (tileSize * (1 - spacing) * 1.5)), 0.0), spriteSheetName, numx, numy, tileSize, LEFT_JUST));
	if (buff.stamina > 0) details.push_back(Text("stamina +" + std::to_string(buff.stamina), Vector3(x, position.y - (lineNum++ * (tileSize * (1 - spacing) * 1.5)), 0.0), spriteSheetName, numx, numy, tileSize, LEFT_JUST));
	if (buff.mana > 0) details.push_back(Text("mana +" + std::to_string(buff.mana), Vector3(x, position.y - (lineNum++ * (tileSize * (1 - spacing) * 1.5)), 0.0), spriteSheetName, numx, numy, tileSize, LEFT_JUST));
	if (buff.attack > 0) details.push_back(Text("attack +" + std::to_string(buff.attack), Vector3(x, position.y - (lineNum++ * (tileSize * (1 - spacing) * 1.5)), 0.0), spriteSheetName, numx, numy, tileSize, LEFT_JUST));
	if (buff.defense > 0) details.push_back(Text("defense +" + std::to_string(buff.defense), Vector3(x, position.y - (lineNum++ * (tileSize * (1 - spacing) * 1.5)), 0.0), spriteSheetName, numx, numy, tileSize, LEFT_JUST));
	if (buff.blockPercent > 0) details.push_back(Text("block +" + std::to_string(buff.blockPercent) + "%", Vector3(x, position.y - (lineNum++ * (tileSize * (1 - spacing) * 1.5)), 0.0), spriteSheetName, numx, numy, tileSize, LEFT_JUST));
	if (buff.manaReduction > 0) details.push_back(Text("mana cost -" + std::to_string(buff.manaReduction) + "%", Vector3(x, position.y - (lineNum++ * (tileSize * (1 - spacing) * 1.5)), 0.0), spriteSheetName, numx, numy, tileSize, LEFT_JUST));
}

DetailedOption::DetailedOption(Passive &passive, Vector3 position, const char *spriteSheetName, int numx, int numy, float tileSize, int alignment, float spacing) : 
	MenuOption(passive.name, position, spriteSheetName, numx, numy, tileSize, tileSize, alignment, spacing), details(), displayDetails(false) {
	float x = position.x + ((1 - alignment / 2.0) * 20) * (tileSize * (1 - spacing)) + tileSize;
	std::vector<std::string> detailList = parseText(passive.description);
	for (int i = 0; i < detailList.size(); ++i)
		details.push_back(Text(detailList[i], Vector3(x, position.y - (i * (tileSize * (1 - spacing) * 1.5)), 0.0), spriteSheetName, numx, numy, tileSize, LEFT_JUST));
}

DetailedOption::DetailedOption(Ability &ability, Vector3 position, const char *spriteSheetName, int numx, int numy, float tileSize, int alignment, float spacing) :
	MenuOption(ability.name, position, spriteSheetName, numx, numy, tileSize, tileSize, alignment, spacing), details(), displayDetails(false) {
	int lineNum = 0;
	float x = position.x + ((1 - alignment / 2.0) * 20) * (tileSize * (1 - spacing)) + tileSize;
	details.push_back(Text("attack: " + std::to_string(ability.attack) + " speed: " + std::to_string(ability.speed), Vector3(x, position.y - (lineNum++ * (tileSize * (1 - spacing) * 1.5)), 0.0), spriteSheetName, numx, numy, tileSize, LEFT_JUST));
	
	std::string cost = "cost:";
	if (ability.hpCost > 0) cost.append(" " + std::to_string(ability.hpCost) + "health");
	if (ability.staminaCost > 0) cost.append(" " + std::to_string(ability.staminaCost) + "stamina");
	if (ability.manaCost > 0) cost.append(" " + std::to_string(ability.manaCost) + "mana");
	details.push_back(Text(cost, Vector3(x, position.y - (lineNum++ * (tileSize * (1 - spacing) * 1.5)), 0.0), spriteSheetName, numx, numy, tileSize, LEFT_JUST));

	std::string stance;
	switch (ability.userStance) {
	case STANCE_COMBAT:
		stance = "combat";
		break;
	case STANCE_SHIELD:
		stance = "shield";
		break;
	case STANCE_AGILE:
		stance = "agile";
		break;
	case STANCE_STUN:
		stance = "stun";
		break;
	default:
		stance = "no change";
		break;
	}
	details.push_back(Text("end stance: " + stance, Vector3(x, position.y - (lineNum++ * (tileSize * (1 - spacing) * 1.5)), 0.0), spriteSheetName, numx, numy, tileSize, LEFT_JUST));

	std::vector<std::string> detailList = parseText(ability.description);
	for (int i = 0; i < detailList.size(); ++i)
		details.push_back(Text(detailList[i], Vector3(x, position.y - (lineNum++ * (tileSize * (1 - spacing) * 1.5)), 0.0), spriteSheetName, numx, numy, tileSize, LEFT_JUST));
}


void DetailedOption::setDetails(int index, std::string newtext) {
	details[index].setText(newtext);
}

void DetailedOption::update(ShaderProgram *program, float mousex, float mousey) {
	if (pointCollision(mousex, mousey)) {
		displayDetails = true;
	}
	else {
		displayDetails = false;
	}
}

void DetailedOption::draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix) {
	Text::draw(program, projectionMatrix, modelMatrix, viewMatrix);
	if (displayDetails) {
		for (unsigned int i = 0; i < details.size(); ++i) {
			details[i].draw(program, projectionMatrix, modelMatrix, viewMatrix);
		}
	}
}