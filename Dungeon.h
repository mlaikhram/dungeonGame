#ifndef MKL_DUNGEON
#define MKL_DUNGEON

#include "DungeonFloorGenerator.h"
#include "DungeonFloor.h"
#include "Text.h"
#include "Player.h"

class Dungeon {
public:
	Dungeon(int id, int floorCounter, int difficulty, std::vector<Enemy> *bosses, Player *player);
	~Dungeon();
	void nextFloor();
	DungeonFloor* generateBossFloor(int index, std::string spriteSheetName);
	std::vector<Enemy>::iterator getEncountered() const;
	int update(ShaderProgram *program, float time);
	int pollAndUpdate(ShaderProgram *program, float &elapsed, float &lastFrameTicks, float &ticks, float &fixedElapsed, SDL_Event &event, const Uint8 *keys);
	void draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix);

private:
	int id;
	int floorCounter;
	int difficulty;
	bool bossFloor;
	//int merchantFloor;
	//Entity merchant;
	Entity transition;
	int transitionPhase;
	DungeonFloorGenerator dfg;
	DungeonFloor *currentFloor;
	Player *player; //shallow
	//int collectedMoney;
	Text floorCountHUD;
	std::vector<Enemy> *bosses; //shallow
};

#endif MKL_DUNGEON