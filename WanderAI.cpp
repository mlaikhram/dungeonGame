#include "WanderAI.h"

WanderAI::WanderAI(float moveAccel, int wanderBuffer) : MoveAI(moveAccel, wanderBuffer) {}

void WanderAI::move(Vector3 &accel, Vector3 &pos, Vector3 &dest, bool obstructed, float maxR, float minR) {
	wander(accel);
}