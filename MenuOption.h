#ifndef MENUOPTION
#define MENUOPTION

#include <string>
#include "Matrix.h"
#include "ShaderProgram.h"
#include "Util.h"

class MenuOption {
public:
	MenuOption(std::string phrase, Vector3 position, const char *spriteSheetName, int numx, int numy, float minSize, float maxSize, float spacing = 0.4f);
	bool pointCollision(float mousex, float mousey);
	void draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix);
	void update(ShaderProgram *program, float mousex, float mouesy);

private:
	Vector3 position;
	float tileSize;
	float minSize;
	float maxSize;
	std::string phrase;
	GLuint spriteSheet;
	int numx;
	int numy;
	float spacing;
};

#endif MENUOPTION