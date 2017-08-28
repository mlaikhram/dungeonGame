#ifndef MKL_BUCKET
#define MKL_BUCKET

//#include <vector>
#include <set>
#include <map>
#include "Util.h"
#include "Ability.h"
#include "Passive.h"
#include "Buff.h"
#include "DetailedOption.h"

class Bucket {
public:
	Bucket(int id, std::string name, Vector3 position, const char *spriteSheetName, int numx, int numy, float tileSize, int currentSP = 0, int alignment = CENTERED, float spacing = 0.4f);

	void add(Ability &ability);
	void add(Passive &passive);
	void add(Buff &buff);

	int operator++();

	void update(ShaderProgram *program, float mousex, float mousey);
	void draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix);

private:
	int id;
	std::string name;

	int currentSP;

	std::set<Ability*,PointerComp<Ability>> abilities;
	std::set<Passive*,PointerComp<Passive>> passives;
	std::set<Buff*,PointerComp<Buff>> buffs;

	std::map<int,DetailedOption> displayContents;

	Vector3 position;
	float tileSize;
	float spacing;
	const std::string spriteSheetName;
	//GLuint spriteSheet;
	int numx;
	int numy;
	int alignment;
};

#endif MKL_BUCKET