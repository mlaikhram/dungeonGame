#include "Bucket.h"

Bucket::Bucket(int id, std::string name, Vector3 position, const char *spriteSheetName, int numx, int numy, float tileSize, int currentSP, int alignment, float spacing) :
	id(id), name(name), position(position), spriteSheetName(spriteSheetName), numx(numx), numy(numy), tileSize(tileSize), currentSP(currentSP), alignment(alignment), spacing(spacing), abilities(), passives(), buffs(), displayContents() {
	// Load the spritesheet
	//spriteSheet = LoadTexture(spriteSheetName);
}

void Bucket::add(Ability &ability) {
	abilities.insert(&ability);
	displayContents.insert(std::pair<int, DetailedOption>(ability.unlockSP, DetailedOption(ability, Vector3(), spriteSheetName.c_str(), numx, numy, tileSize, true, alignment, spacing)));
}

void Bucket::add(Passive &passive) {
	passives.insert(&passive);
	displayContents.insert(std::pair<int, DetailedOption>(passive.unlockSP, DetailedOption(passive, Vector3(), spriteSheetName.c_str(), numx, numy, tileSize, true, alignment, spacing)));
}

void Bucket::add(Buff &buff) {
	buffs.insert(&buff);
	displayContents.insert(std::pair<int, DetailedOption>(buff.unlockSP, DetailedOption(buff, Vector3(), spriteSheetName.c_str(), numx, numy, tileSize, true, alignment, spacing)));
}

int Bucket::operator++() {
	return ++currentSP;
}

void Bucket::update(ShaderProgram *program, float mousex, float mousey) {
	for (std::map<int, DetailedOption>::iterator it = displayContents.begin(); it != displayContents.end(); ++it) {
		(it->second).update(program, mousex, mousey);
	}
}

void Bucket::draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix) {
	int itemNum = 0;
	//Text(name, Vector3(), "letters.png", 16, 16, 0.1f).draw(program, projectionMatrix, modelMatrix, viewMatrix);
	//itemNum++;
	for (std::map<int, DetailedOption>::iterator it = displayContents.begin(); it != displayContents.end(); ++it) {
		(it->second).setX(0.0f);
		(it->second).setY(itemNum++ * (it->second).tileSize);
		(it->second).draw(program, projectionMatrix, modelMatrix, viewMatrix);
	}
}