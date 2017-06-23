#include "MenuOption.h"

#include <string>

MenuOption::MenuOption(std::string p, Vector3 position, const char *spriteSheetName, int numx, int numy, float minSize, float maxSize) : position(position), numx(numx), numy(numy), tileSize(minSize), minSize(minSize), maxSize(maxSize) {
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

bool MenuOption::pointCollision(float mousex, float mousey) { // TODO: IDK IF THIS WORKS
	float left = position.x - tileSize / 2.0f;
	float right = left + lengthOfPhrase * tileSize - (.4f * tileSize * lengthOfPhrase); //subtract for spacing
	float top = position.y + tileSize / 2.0f;
	float bottom = top - tileSize;
	return (mousex > left && mousex < right && mousey > bottom && mousey < top);
}

void MenuOption::draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix) {
	for (int i = 0; i < lengthOfPhrase; ++i) {
		modelMatrix.identity();
		modelMatrix.Translate((position.x + i*tileSize - (.4f * tileSize * i)), position.y, 0.0f); //subtract for spacing
		program->setModelMatrix(modelMatrix);
		program->setProjectionMatrix(projectionMatrix);
		program->setViewMatrix(viewMatrix);
		DrawSpriteSheetSprite(program, phrase[i], numx, numy, spriteSheet, tileSize);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MenuOption::update(ShaderProgram *program, float mousex, float mousey) {
	if (pointCollision(mousex, mousey))
		tileSize = maxSize;
	else
		tileSize = minSize;
}