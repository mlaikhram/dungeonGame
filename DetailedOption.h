#ifndef MKL_DETAILEDOPTION
#define MKL_DETAILEDOPTION

#include <vector>
#include "MenuOption.h"
#include "Buff.h"
#include "Ability.h"
#include "Passive.h"

class Buff;

class DetailedOption : public MenuOption {
public:
	//single line of text
	DetailedOption(std::string phrase, Vector3 position, std::string detail, Vector3 detailPos, const char *spriteSheetName, int numx, int numy, float size, int alignment = CENTERED, int detailedAlign = CENTERED, float spacing = 0.4f);
	//multiple lines of text
	DetailedOption(std::string phrase, Vector3 position, std::vector<std::string> detailList, Vector3 detailPos, const char *spriteSheetName, int numx, int numy, float size, int alignment = CENTERED, int detailedAlign = CENTERED, float spacing = 0.4f);
	//buff
	DetailedOption(Buff &buff, Vector3 position, const char *spriteSheetName, int numx, int numy, float tileSize, int alignment = CENTERED, float spacing = 0.4f);
	//passive
	DetailedOption(Passive &passive, Vector3 position, const char *spriteSheetName, int numx, int numy, float tileSize, int alignment = CENTERED, float spacing = 0.4f);

	void setDetails(int index, std::string newtext);
	void update(ShaderProgram *program, float mousex, float mousey);
	void draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix);

private:
	std::vector<Text> details;
	bool displayDetails;
};

#endif MKL_DETAILEDOPTION