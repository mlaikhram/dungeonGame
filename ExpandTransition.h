#ifndef MKL_EXPANDTRANSITION
#define MKL_EXPANDTRANSITION

#include "Transition.h"
#include "Entity.h"

class ExpandTransition : public Transition {
public:
	ExpandTransition(Entity *player, Entity expander, float growthRate = 0.1f, float maxSize = 8.0f);

	virtual bool fullGrow();
	virtual bool fullShrink();

	virtual void growStep(float &fixedElapsed);
	virtual void shrinkStep(float &fixedElapsed);

	virtual void draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix);

protected:
	//set coordinates of the transition relative to the player
	virtual void recenter();

private:
	Entity expander;
	float growthRate;
	float maxSize;
};

#endif MKL_EXPANDTRANSITION