#ifndef MKL_TIERLIST
#define MKL_TIERLIST

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

template <class obj> class TierList {
public:
	TierList(std::vector<std::vector<obj>> tierList, int current = 0, int deviation = 2);
	void display(std::ofstream &ofs = std::cout);
	// returns a vector containing weighted random objects from current tier within the deviation
	std::vector<obj> spawnObjects(int size);
	int getTier();
	int operator++();
	int operator--();

private:
	int current;								// mean index in the tier list
	int deviation;								// max value to deviate from the current index
	std::vector<std::vector<obj>> tierList;

	// returns a vector containing the weights of pulling from each of the tiers within the deviation
	std::vector<int> weightList();
};

template <class obj>
TierList<obj>::TierList(std::vector<std::vector<obj>> tierList, int current, int deviation) : tierList(tierList), current(current), deviation(deviation) {}

template <class obj>
void TierList<obj>::display(std::ofstream &ofs) {
	for (unsigned int i = 0; i < tierList.size(); ++i) {
		ofs << "Tier " << i << std::endl;
		for (obj item : tierList[i]) {
			ofs << item << std::endl;
		}
		ofs << std::endl;
	}
}

// returns a vector containing weighted random objects from current tier within the deviation
template <class obj>
std::vector<obj> TierList<obj>::spawnObjects(int size) {
	std::vector<obj> spawns(0);
	std::vector<int> weights = weightList();
	for (int i = 0; i < size; ++i) {
		int tier = weights[rand() % weights.size()];
		//std::cout << "tier: " << tier << std::endl;
		spawns.push_back(tierList[tier][rand() % tierList[tier].size()]);
	}
	return spawns;
}

template <class obj>
int TierList<obj>::getTier() {
	return current;
}

template <class obj>
int TierList<obj>::operator++() {
	return ++current;
}

template <class obj>
int TierList<obj>::operator--() {
	return --current;
}

// returns a vector containing the weights of pulling from each of the tiers within the deviation
template <class obj>
std::vector<int> TierList<obj>::weightList() {
	std::vector<int> weightList;
	// loop within the deviation
	for (int i = current - deviation; i <= current + deviation; ++i) {
		// determine probability function
		int dev = abs(i - current);
		int weight;
		if (dev == 2) weight = 1;
		else if (dev == 1) weight = 4;
		else if (dev == 0) weight = 10;
		for (int j = 0; j < weight; ++j) {
			// prevent index out of bound
			if (i < 0)
				weightList.push_back(0);
			else if (i >= tierList.size())
				weightList.push_back(tierList.size() - 1);
			else
				weightList.push_back(i);
		}
	}
	//for (int x : weightList)
	//	std::cout << x << std::endl;
	return weightList;
}

#endif MKL_TIERLIST