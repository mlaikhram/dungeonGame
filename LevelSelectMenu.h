#ifndef LEVELSELECTMENU
#define LEVELSELECTMENU

#include "Matrix.h"
#include "ShaderProgram.h"
#include "Menu.h"
#include "Util.h"

class LevelSelectMenu : public Menu {
public:
	LevelSelectMenu();
	int update(ShaderProgram *program, float time, float mousex, float mousey, int mousedOption);
	int dungeonSelected, floorSelected, difficultySelected;
};

#endif LEVELSELECTMENU