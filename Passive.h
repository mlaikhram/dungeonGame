#ifndef MKL_PASSIVE
#define MKL_PASSIVE

#include <fstream>

class Passive {
public:
	Passive(int id, std::string name, std::string description, int timing, std::string filename, int unlockLevel, int unlockSP);

	bool operator<(const Passive &rhs) const;

	~Passive();

	int id;
	std::string name;
	std::string description;

	int timing;

	std::ifstream script;

	int unlockLevel;
	int unlockSP;
};

#endif MKL_PASSIVE