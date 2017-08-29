#ifndef MKL_TRANSITION
#define MKL_TRANSITION

#include "Util.h"
#include "Entity.h"

class Transition {
public:
	Transition(Entity *player) : active(false), growing(true), player(player) {}

	//return false if reached max growth or inactive
	virtual void grow(float &elapsed, float &lastFrameTicks, float &ticks, float &fixedElapsed) = 0;
	//return false if reached min shrink or inactive
	virtual void shrink(float &elapsed, float &lastFrameTicks, float &ticks, float &fixedElapsed) = 0;

	virtual void draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix) = 0;

	bool active;
	bool growing;

protected:
	//set coordinates of the transition relative to the player
	virtual void recenter() = 0;
	
	Entity *player; //shallow

};

#endif MKL_TRANSITION