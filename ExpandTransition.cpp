#include "ExpandTransition.h"

ExpandTransition::ExpandTransition(Entity *player, Entity expander, float growthRate, float maxSize) : Transition(player), expander(expander), growthRate(growthRate), maxSize(maxSize) {}

void ExpandTransition::recenter() {
	expander.position = player->position;
}

bool ExpandTransition::grow(float &elapsed, float &lastFrameTicks, float &ticks, float &fixedElapsed) {
	if (!active || expander.size >= maxSize) {
		expander.size = maxSize;
		growing = false;
		return false;
	}
	if (!growing) return true;

	recenter();

	//timestep
	ticks = (float)SDL_GetTicks() / 1000.0f;
	elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;

	fixedElapsed = elapsed;
	if (fixedElapsed > FIXED_TIMESTEP * MAX_TIMESTEPS) {
		fixedElapsed = FIXED_TIMESTEP * MAX_TIMESTEPS;
	}
	/*while (fixedElapsed >= FIXED_TIMESTEP) {
		fixedElapsed -= FIXED_TIMESTEP;
		expander.size += growthRate;
	}*/
	expander.size += growthRate;// *fixedElapsed;

	return true;
}

bool ExpandTransition::shrink(float &elapsed, float &lastFrameTicks, float &ticks, float &fixedElapsed) {
	if (!active || expander.size <= 0.0f) {
		expander.size = 0.0f;
		growing = true;
		active = false;
		return false;
	}
	if (growing) return true;

	recenter();

	//timestep
	ticks = (float)SDL_GetTicks() / 1000.0f;
	elapsed = ticks - lastFrameTicks;
	lastFrameTicks = ticks;

	fixedElapsed = elapsed;
	if (fixedElapsed > FIXED_TIMESTEP * MAX_TIMESTEPS) {
		fixedElapsed = FIXED_TIMESTEP * MAX_TIMESTEPS;
	}
	/*while (fixedElapsed >= FIXED_TIMESTEP) {
	fixedElapsed -= FIXED_TIMESTEP;
	expander.size += growthRate;
	}*/
	expander.size -= growthRate;// * fixedElapsed;

	return true;
}

void ExpandTransition::draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix) {
	expander.draw(program, projectionMatrix, modelMatrix, viewMatrix);
}
