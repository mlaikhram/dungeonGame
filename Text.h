#ifndef MKL_TEXT
#define MKL_TEXT

#include "Util.h"

class Text {
public:
	Text(std::string text, Vector3 position, const char *spriteSheetName, int numx, int numy, float tileSize, int alignment = CENTERED, float spacing = 0.4f);
	float getTileSize();
	void setText(std::string newtext);
	virtual void draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix);

	Vector3 position;

protected:
	float tileSize;
	std::string text;
	GLuint spriteSheet;
	int numx;
	int numy;
	float spacing;
	int alignment;
};

#endif MKL_TEXT