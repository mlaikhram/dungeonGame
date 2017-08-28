#include "Bucket.h"

Bucket::Bucket(int id, std::string name, Vector3 position, const char *spriteSheetName, int numx, int numy, float tileSize, int currentSP, int alignment, float spacing) :
	id(id), name(name), displayName(name + ": " + std::to_string(currentSP), Vector3(), spriteSheetName, numx, numy, tileSize, alignment, spacing), 
	position(position), spriteSheetName(spriteSheetName), numx(numx), numy(numy), tileSize(tileSize), currentSP(currentSP), alignment(alignment), spacing(spacing), abilities(), passives(), buffs(), displayContents() {
	// Load the spritesheet
	//spriteSheet = LoadTexture(spriteSheetName);
}

void Bucket::add(Ability &ability) {
	abilities.insert(&ability);
	displayContents.insert(std::pair<Text, DetailedOption>(Text(std::to_string(ability.unlockSP), Vector3(), spriteSheetName.c_str(), numx, numy, tileSize, RIGHT_JUST, spacing), 
		DetailedOption(ability, Vector3(), spriteSheetName.c_str(), numx, numy, tileSize, true, alignment, spacing)));
}

void Bucket::add(Passive &passive) {
	passives.insert(&passive);
	displayContents.insert(std::pair<Text, DetailedOption>(Text(std::to_string(passive.unlockSP), Vector3(), spriteSheetName.c_str(), numx, numy, tileSize, RIGHT_JUST, spacing),
		DetailedOption(passive, Vector3(), spriteSheetName.c_str(), numx, numy, tileSize, true, alignment, spacing)));
	//displayContents.insert(std::pair<int, DetailedOption>(passive.unlockSP, DetailedOption(passive, Vector3(), spriteSheetName.c_str(), numx, numy, tileSize, true, alignment, spacing)));
}

void Bucket::add(Buff &buff) {
	buffs.insert(&buff);
	displayContents.insert(std::pair<Text, DetailedOption>(Text(std::to_string(buff.unlockSP), Vector3(), spriteSheetName.c_str(), numx, numy, tileSize, RIGHT_JUST, spacing),
		DetailedOption(buff, Vector3(), spriteSheetName.c_str(), numx, numy, tileSize, true, alignment, spacing)));
	//displayContents.insert(std::pair<int, DetailedOption>(buff.unlockSP, DetailedOption(buff, Vector3(), spriteSheetName.c_str(), numx, numy, tileSize, true, alignment, spacing)));
}

int Bucket::operator++() {
	displayName.setText(name + ": " + std::to_string(++currentSP));
	return currentSP;
}

void Bucket::update(ShaderProgram *program, float mousex, float mousey) {
	for (std::map<Text, DetailedOption>::iterator it = displayContents.begin(); it != displayContents.end(); ++it) {
		(it->second).update(program, mousex, mousey);
	}
}

void Bucket::draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix) {
	int itemNum = 1;
	//Text(name, Vector3(), "letters.png", 16, 16, 0.1f).draw(program, projectionMatrix, modelMatrix, viewMatrix);
	//itemNum++;
	displayName.position.x = position.x;
	displayName.position.y = position.y;
	displayName.draw(program, projectionMatrix, modelMatrix, viewMatrix);

	for (std::map<Text, DetailedOption>::iterator it = displayContents.begin(); it != displayContents.end(); ++it) {
		(it->first).position.x = position.x - ((alignment / 2.0) * MAX_NAME_LENGTH) * (tileSize * (1.0 - spacing)) - tileSize;
		(it->first).position.y = position.y + itemNum * (it->second).tileSize;
		(it->first).draw(program, projectionMatrix, modelMatrix, viewMatrix);

		(it->second).setX(0.0f);
		(it->second).setY(itemNum++ * (it->second).tileSize);
		(it->second).draw(program, projectionMatrix, modelMatrix, viewMatrix);
	}
}