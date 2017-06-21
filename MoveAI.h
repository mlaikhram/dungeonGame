#ifndef MKL_MOVEAI
#define MKL_MOVEAI

#include "Util.h"

class MoveAI {
public:
	MoveAI(float moveAccel = 10.0f, float wanderInterval = 0.25f, int wanderBuffer = 2);
	void update(float time);
	void wander(Vector3 &accel);
	virtual void move(Vector3 &accel, Vector3 &pos, Vector3 &dest, bool obstructed, float maxR, float minR = 0.0f) = 0;

protected:
	float moveAccel;
	int wanderBuffer;
	float timer;
	float wanderInterval;
};

#endif MKL_MOVEAI