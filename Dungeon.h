#ifndef MKL_DUNGEON
#define MKL_DUNGEON

#include "DungeonFloorGenerator.h"
#include "DungeonFloor.h"

class Dungeon {
public:
	Dungeon(int id, int floorCounter, int difficulty, Entity *player);
	void nextFloor();
	int update(ShaderProgram *program, float time);
	int pollAndUpdate(ShaderProgram *program, float &elapsed, float &lastFrameTicks, float &ticks, float &fixedElapsed, SDL_Event &event, const Uint8 *keys);
	void draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix);

private:
	int id;
	int floorCounter;
	int difficulty;
	//int merchantFloor;
	//Entity merchant;
	DungeonFloorGenerator dfg;
	DungeonFloor *currentFloor;
	Entity *player;
};

#endif MKL_DUNGEON