#ifndef MKL_TEXT
#define MKL_TEXT

#include "Util.h"

class Text {
public:
	Text(std::string text, Vector3 position, const char *spriteSheetName, int numx, int numy, float tileSize, int alignment = CENTERED, float spacing = 0.4f);
	float getTileSize();
	void setText(std::string newtext);
	virtual void draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix);

	std::string text;
	Vector3 position;
	float tileSize;
	float spacing;

protected:
	GLuint spriteSheet;
	int numx;
	int numy;
	int alignment;
};

#endif MKL_TEXT