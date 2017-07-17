#ifndef MAINMENU
#define MAINMENU

#include "Menu.h"

class MainMenu : public Menu {
public:
	MainMenu();
	int update(ShaderProgram *program, float time, float mousex, float mousey, int mousedOption);
};

#endif MAINMENU