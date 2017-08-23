#include "Bucket.h"

Bucket::Bucket(int id, std::string name, int currentSP) : 
	id(id), name(name), currentSP(currentSP), abilities(), passives(), buffs(), displayContents() {}