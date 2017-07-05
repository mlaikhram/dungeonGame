#ifndef MKL_WANDERAI
#define MKL_WANDERAI

#include "MoveAI.h"

class WanderAI : public MoveAI {
public:
	WanderAI(float moveAccel = 10.0f, float wanderInterval = 0.25f, int wanderBuffer = 2);
	virtual void move(DungeonFloor *floor, Vector3 &accel, Vector3 &pos, Vector3 &dest = Vector3(), float maxR = 0.0f, float minR = 0.0f);
	virtual MoveAI* clone();
};

#endif MKL_WANDERAI