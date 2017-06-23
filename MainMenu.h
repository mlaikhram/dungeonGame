#ifndef MAINMENU
#define MAINMENU

#include "Matrix.h"
#include "ShaderProgram.h"
#include "MenuScreen.h"
#include "Util.h"
#include <vector>

class MainMenu {
public:
	MainMenu();
	void draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix);
	int update(ShaderProgram *program, float time, float mousex, float mousey, int mousedOption);
	int pollAndUpdate(ShaderProgram *program, float &elapsed, float &lastFrameTicks, float &ticks, float &fixedElapsed, SDL_Event &event);

private:
	std::vector<MenuScreen> menuScreens;
	int activeScreen;
};

#endif MAINMENU