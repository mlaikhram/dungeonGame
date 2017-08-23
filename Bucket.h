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
	Bucket(int id, std::string name, int currentSP = 0);

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
};

#endif MKL_BUCKET