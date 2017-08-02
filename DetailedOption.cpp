#include "DetailedOption.h"

DetailedOption::DetailedOption(std::string phrase, Vector3 position, std::string details, Vector3 detailsPos, const char *spriteSheetName, int numx, int numy, float tileSize, int alignment, int detailedAlign, float spacing) :
	MenuOption(phrase, position, spriteSheetName, numx, numy, tileSize, tileSize, alignment, spacing), details(details, detailsPos, spriteSheetName, numx, numy, tileSize, detailedAlign, spacing), displayDetails(false) {}

void DetailedOption::setDetails(std::string newtext) {
	details.setText(newtext);
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
		details.draw(program, projectionMatrix, modelMatrix, viewMatrix);
	}
}