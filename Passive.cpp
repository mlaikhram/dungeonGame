#include "Passive.h"

Passive::Passive(int id, std::string name, std::string description, int timing, std::string filename, int unlockLevel, int unlockSP) : 
	id(id), name(name), description(description), timing(timing), unlockLevel(unlockLevel), unlockSP(unlockSP), script(filename) {}

bool Passive::operator<(const Passive &rhs) const {
	return unlockSP < rhs.unlockSP;
}

Passive::~Passive() {
	script.close();
}