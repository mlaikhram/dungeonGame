#include "Passive.h"

Passive::Passive(int id, std::string name, std::string description, std::string filename, int unlockLevel) : 
	id(id), name(name), description(description), unlockLevel(unlockLevel), script(filename) {}

Passive::~Passive() {
	script.close();
}