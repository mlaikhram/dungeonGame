#ifndef MKL_DETAILEDOPTION
#define MKL_DETAILEDOPTION

#include "MenuOption.h"

class DetailedOption : public MenuOption {
public:
	DetailedOption(std::string phrase, Vector3 position, std::string details, Vector3 detailsPos, const char *spriteSheetName, int numx, int numy, float size, int alignment = CENTERED, int detailedAlign = CENTERED, float spacing = 0.4f);

	void setDetails(std::string newtext);
	void update(ShaderProgram *program, float mousex, float mousey);
	void draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix);

private:
	Text details;
	bool displayDetails;
};

#endif MKL_DETAILEDOPTION