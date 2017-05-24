#include "MenuOption.h"

#include <string>

MenuOption::MenuOption(std::string p, Vector3 position, const char *spriteSheetName, int numx, int numy, float tileSize) : position(position), numx(numx), numy(numy), tileSize(tileSize) {
	// Convert string 'p' into char array phrase
	phrase = new char[p.length()];
	for (int i = 0; i < p.length(); ++i) {
		phrase[i] = p.at(i);
	}

	// Store length of phrase
	lengthOfPhrase = p.length();

	// Load the spritesheet
	spriteSheet = LoadTexture(spriteSheetName);
}

float MenuOption::getWidth() {
	return width;
}

float MenuOption::getHeight() {
	return height;
}

bool MenuOption::pointCollision(float mousex, float mousey) {
	return (position.x < mousex < position.x + width && position.y < mousey < position.y + height);
}

void MenuOption::draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix) {
	for (int i = 0; i < lengthOfPhrase; ++i) {
		modelMatrix.identity();
		modelMatrix.Translate((position.x + i*tileSize) * 0.6f, position.y, 0.0f);
		program->setModelMatrix(modelMatrix);
		program->setProjectionMatrix(projectionMatrix);
		program->setViewMatrix(viewMatrix);
		DrawSpriteSheetSprite(program, phrase[i], numx, numy, spriteSheet, tileSize);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}