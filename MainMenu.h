#ifndef MAINMENU
#define MAINMENU

#include "Matrix.h"
#include "ShaderProgram.h"
#include "MenuScreen.h"
#include "Menu.h"
#include "Util.h"
#include <vector>

class MainMenu : public Menu {
public:
	MainMenu();
	int update(ShaderProgram *program, float time, float mousex, float mousey, int mousedOption);
};

#endif MAINMENU