#ifndef MENUOPTION
#define MENUOPTION

#include <string>
#include "Matrix.h"
#include "ShaderProgram.h"
#include "Text.h"
#include "Util.h"

class MenuOption : public Text {
public:
	MenuOption(std::string phrase, Vector3 position, const char *spriteSheetName, int numx, int numy, float minSize, float maxSize, int alignment = CENTERED, float spacing = 0.4f);
	bool pointCollision(float mousex, float mousey);
	void update(ShaderProgram *program, float mousex, float mouesy);
	void reset();

private:
	float minSize;
	float maxSize;
};

#endif MENUOPTION