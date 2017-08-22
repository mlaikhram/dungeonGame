#ifndef MKL_BUCKET
#define MKL_BUCKET

#include <vector>
#include "Ability.h"
#include "Passive.h"
#include "Buff.h"
#include "DetailedOption.h"

class Bucket {
public:
	Bucket(int id, std::string name, std::vector<Ability*> abilities, std::vector<Passive*> passives, std::vector<Buff*> buffs, int currentSP = 0);



private:
	int id;
	std::string name;

	int currentSP;

	std::vector<Ability*> abilities;
	std::vector<Passive*> passives;
	std::vector<Buff*> buffs;

	std::vector<DetailedOption> displayContents;
};

#endif MKL_BUCKET