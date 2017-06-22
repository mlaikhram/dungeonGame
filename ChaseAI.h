#ifndef MKL_CHASEAI
#define MKL_CHASEAI

#include "MoveAI.h"

class ChaseAI : public MoveAI {
public:
	ChaseAI(float moveAccel = 10.0f, float wanderInterval = 0.25f, int wanderBuffer = 2);
	virtual void move(DungeonFloor *floor, Vector3 &accel, Vector3 &pos, Vector3 &dest, float maxR, float minR = 0.0f);
	bool isObstructed(Vector3 start, Vector3 end, DungeonFloor *floor, float spacing);
};

#endif MKL_CHASEAI