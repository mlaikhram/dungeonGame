#include "MoveAI.h"

MoveAI::MoveAI(float moveAccel, float wanderInterval, int wanderBuffer) : moveAccel(moveAccel), wanderInterval(wanderInterval), wanderBuffer(wanderBuffer), timer(0.0f) {}

void MoveAI::update(float time) {
	timer += time;
	if (timer > wanderInterval) timer = 0.0f;
}

//randomly set accel to any direction or 0 using the moveAccel value
void MoveAI::wander(Vector3 &accel) {
	int random = (int)(rand() % (8 + wanderBuffer));
	float angle = (int)(rand() % 360) * PI / 180.0f;

	switch (random) {
	case 0:
		accel.x = moveAccel * cos(angle);
		accel.y = moveAccel * sin(angle);
		//accel.x = -moveAccel;
		//accel.y = moveAccel;
		break;

	/*case 1:
		accel.x = 0.0f;
		accel.y = moveAccel;
		break;

	case 2:
		accel.x = moveAccel;
		accel.y = moveAccel;
		break;

	case 3:
		accel.x = -moveAccel;
		accel.y = 0.0f;
		break;

	case 4:
		accel.x = moveAccel;
		accel.y = 0.0f;
		break;

	case 5:
		accel.x = -moveAccel;
		accel.y = -moveAccel;
		break;

	case 6:
		accel.x = 0.0f;
		accel.y = -moveAccel;
		break;

	case 7:
		accel.x = moveAccel;
		accel.y = -moveAccel;
		break;
	*/
	default:
		accel.x = 0.0f;
		accel.y = 0.0f;
		break;
	}
	accel.z = 0.0f;
}