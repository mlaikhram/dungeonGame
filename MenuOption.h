#ifndef MENUOPTION
#define MENUOPTION

#include <string>
#include "Matrix.h"
#include "ShaderProgram.h"
#include "Util.h"

class MenuOption {
public:
	//MenuOption(); // Constructors
	MenuOption(std::string p, Vector3 position, const char *spriteSheetName, int numx, int numy, float scale);
	float getWidth();
	float getHeight();
	bool pointCollision(float mousex, float mousey);
	void draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix);

private:
	Vector3 position;
	float width, height;
	float tileSize;
	char* phrase;
	int lengthOfPhrase;
	GLuint spriteSheet;
	int numx;
	int numy;
};

#endif MENUOPTION