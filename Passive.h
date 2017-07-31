#ifndef MKL_PASSIVE
#define MKL_PASSIVE

#include <fstream>

class Passive {
public:
	Passive(int id, std::string name, std::string description, int timing, std::string filename, int unlockLevel);
	~Passive();

	int id;
	std::string name;
	std::string description;

	int timing;

	std::ifstream script;

	int unlockLevel;
};

#endif MKL_PASSIVE