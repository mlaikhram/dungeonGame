#ifndef MKL_TEXT
#define MKL_TEXT

#include "Util.h"

class Text {
public:
	Text(std::string text, Vector3 position, const char *spriteSheetName, int numx, int numy, float tileSize, int alignment = CENTERED, float spacing = 0.4f);
	void draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix);

protected:
	Vector3 position;
	float tileSize;
	std::string text;
	GLuint spriteSheet;
	int numx;
	int numy;
	float spacing;
	int alignment;
};

#endif MKL_TEXT