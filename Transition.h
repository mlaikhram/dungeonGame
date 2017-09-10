#ifndef MKL_TRANSITION
#define MKL_TRANSITION

#include "Util.h"
#include "Player.h"

class Transition {
public:
	Transition(Player *player);

	//return false if reached max growth or inactive
	void grow(float &elapsed, float &lastFrameTicks, float &ticks, float &fixedElapsed);
	//return false if reached min shrink or inactive
	void shrink(float &elapsed, float &lastFrameTicks, float &ticks, float &fixedElapsed);

	//determines if the transition fully covers the screen / is completely invisible
	virtual bool fullGrow() = 0;
	virtual bool fullShrink() = 0;

	//determines one incrememnt of grow/shrink
	virtual void growStep(float &fixedElapsed) = 0;
	virtual void shrinkStep(float &fixedElapsed) = 0;

	virtual void draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix) = 0;

	bool active;
	bool growing;

protected:
	//set coordinates of the transition relative to the player
	virtual void recenter() = 0;
	
	Player *player; //shallow

};

#endif MKL_TRANSITION