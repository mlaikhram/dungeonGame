#include "Text.h"

Text::Text(std::string text, Vector3 position, const char *spriteSheetName, int numx, int numy, float tileSize, int alignment, float spacing) :
	text(text), position(position), numx(numx), numy(numy), tileSize(tileSize), spacing(spacing), alignment(alignment) {
	// Load the spritesheet
	spriteSheet = LoadTexture(spriteSheetName);
}

void Text::draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix) {
	//float width = (position.x + (lengthOfPhrase - 1) * tileSize * spacing + tileSize / 2) - (position.x - tileSize / 2);
	float width = text.length() * (tileSize - spacing * tileSize) - tileSize / 2;

	for (int i = 0; i < text.length(); ++i) {
		modelMatrix.identity();
		modelMatrix.Translate((position.x + i*tileSize - (spacing * tileSize * i)) - alignment * (width / 2), position.y, 0.0f); //subtract for spacing
		program->setModelMatrix(modelMatrix);
		program->setProjectionMatrix(projectionMatrix);
		program->setViewMatrix(viewMatrix);
		DrawSpriteSheetSprite(program, text[i], numx, numy, spriteSheet, tileSize);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}