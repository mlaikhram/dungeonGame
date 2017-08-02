#include "Bucket.h"

Bucket::Bucket(int id, std::string name, std::vector<Ability*> abilities, std::vector<Passive*> passives, std::vector<Buff*> buffs, int currentSP) : 
	id(id), name(name), abilities(abilities), passives(passives), buffs(buffs), currentSP(currentSP) {}