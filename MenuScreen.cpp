#include "MenuScreen.h"

MenuScreen::MenuScreen(std::vector<MenuOption> &menuOptions) : menuOptions(menuOptions) {

}

void MenuScreen::draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix) {
	for (MenuOption &m : menuOptions) {
		m.draw(program, projectionMatrix, modelMatrix, viewMatrix);
	}
}

void MenuScreen::update(ShaderProgram *program, float time, float mousex, float mousey) {
	for (MenuOption &m : menuOptions) {
		m.update(program, mousex, mousey);
	}
}

int MenuScreen::mousedOption(float mousex, float mousey) {
	for (int i = 0; i < menuOptions.size(); ++i) {
		if (menuOptions[i].pointCollision(mousex, mousey))
			return i;
	}
	return -1;
}