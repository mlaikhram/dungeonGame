#ifndef MKL_MENU
#define MKL_MENU

#include "MenuScreen.h"
#include "Util.h"
#include <vector>

class Menu {
public:
	Menu();
	void draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix);
	virtual int update(ShaderProgram *program, float time, float mousex, float mousey, int mousedOption) = 0;
	int pollAndUpdate(ShaderProgram *program, float &elapsed, float &lastFrameTicks, float &ticks, float &fixedElapsed, SDL_Event &event);

protected:
	std::vector<MenuScreen> menuScreens;
	int activeScreen;
};

#endif MKL_MENU