#include "MenuOption.h"

#include <string>

MenuOption::MenuOption(std::string text, Vector3 position, const char *spriteSheetName, int numx, int numy, float minSize, float maxSize, int alignment, float spacing) : 
	Text(text, position, spriteSheetName, numx, numy, minSize, alignment, spacing), minSize(minSize), maxSize(maxSize) {}

bool MenuOption::pointCollision(float mousex, float mousey) {
	float width = text.length() * (tileSize - spacing * tileSize) - tileSize / 2;

	float left = position.x - tileSize / 2.0f - alignment * (width / 2);
	float right = left + text.length() * tileSize - (spacing * tileSize * text.length()); //subtract for spacing
	float top = position.y + tileSize / 2.0f;
	float bottom = top - tileSize;
	return (mousex > left && mousex < right && mousey > bottom && mousey < top);
}

void MenuOption::update(ShaderProgram *program, float mousex, float mousey) {
	if (pointCollision(mousex, mousey))
		tileSize = maxSize;
	else
		tileSize = minSize;
}