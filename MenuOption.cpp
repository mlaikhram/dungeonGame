#include "MenuOption.h"

#include <string>

MenuOption::MenuOption(std::string phrase, Vector3 position, const char *spriteSheetName, int numx, int numy, float minSize, float maxSize, float spacing) : 
	phrase(phrase), position(position), numx(numx), numy(numy), tileSize(minSize), minSize(minSize), maxSize(maxSize), spacing(spacing) {
	// Load the spritesheet
	spriteSheet = LoadTexture(spriteSheetName);
}

bool MenuOption::pointCollision(float mousex, float mousey) {
	float width = phrase.length() * (tileSize - spacing * tileSize) - tileSize / 2;

	float left = position.x - tileSize / 2.0f - width / 2;
	float right = left + phrase.length() * tileSize - (spacing * tileSize * phrase.length()); //subtract for spacing
	float top = position.y + tileSize / 2.0f;
	float bottom = top - tileSize;
	return (mousex > left && mousex < right && mousey > bottom && mousey < top);
}

void MenuOption::draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix) {

	//float width = (position.x + (lengthOfPhrase - 1) * tileSize * spacing + tileSize / 2) - (position.x - tileSize / 2);
	float width = phrase.length() * (tileSize - spacing * tileSize) - tileSize / 2;

	for (int i = 0; i < phrase.length(); ++i) {
		modelMatrix.identity();
		modelMatrix.Translate((position.x + i*tileSize - (spacing * tileSize * i)) - width / 2, position.y, 0.0f); //subtract for spacing
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