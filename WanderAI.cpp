#include "WanderAI.h"

WanderAI::WanderAI(float moveAccel, float timeCycle, int wanderInterval) : MoveAI(moveAccel, timeCycle, wanderInterval) {}

void WanderAI::move(DungeonFloor *floor, Vector3 &accel, Vector3 &pos, Vector3 &dest, float maxR, float minR) {
	if (timer == 0.0f) {
		if (accel.isZero())
			wander(accel);
		else {
			accel.x = 0.0f;
			accel.y = 0.0f;
			accel.z = 0.0f;
		}
	}
}