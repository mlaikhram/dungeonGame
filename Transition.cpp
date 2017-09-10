#include "Transition.h"

Transition::Transition(Player *player) : active(false), growing(true), player(player) {}

void Transition::grow(float &elapsed, float &lastFrameTicks, float &ticks, float &fixedElapsed) {

	if (fullGrow()) {
		growing = false;
		return;
	}

	active = true;
	growing = true;

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
	}*/
	growStep(fixedElapsed);
}

void Transition::shrink(float &elapsed, float &lastFrameTicks, float &ticks, float &fixedElapsed) {

	if (fullShrink()) {
		active = false;
		growing = true;
		return;
	}

	active = true;
	growing = false;

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
	}*/
	shrinkStep(fixedElapsed);
}