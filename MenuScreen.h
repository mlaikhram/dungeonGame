#ifndef MAINSCREEN
#define MAINSCREEN

#include "Matrix.h"
#include "ShaderProgram.h"
#include "MenuOption.h"
#include <vector>

class MenuScreen {
public:
	MenuScreen(std::vector<MenuOption> &menuOptions);
	void draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix);
	void update(ShaderProgram *program, float time, float mousex, float mousey);
	int mousedOption(float mousex, float mousey);

private:
	std::vector<MenuOption> menuOptions;
};

#endif MAINSCREEN