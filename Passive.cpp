#include "Passive.h"

Passive::Passive(int id, std::string name, std::string description, int timing, std::string filename, int unlockLevel) : 
	id(id), name(name), description(description), timing(timing), unlockLevel(unlockLevel), script(filename) {}

Passive::~Passive() {
	script.close();
}