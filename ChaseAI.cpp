#include "ChaseAI.h"

ChaseAI::ChaseAI(float moveAccel, float timeCycle, int wanderInterval) : MoveAI(moveAccel, timeCycle, wanderInterval) {}

bool ChaseAI::isObstructed(Vector3 start, Vector3 end, DungeonFloor *floor, float spacing) {
	//calculate midpoint
	Vector3 mid((end.x + start.x) / 2, (end.y + start.y) / 2, (end.z + start.z) / 2);
	//check if midpoint is an obstruction
	int x, y;
	worldToTileCoordinates(mid.x, mid.y, x, y, floor->getMapSize());
	if (!floor->floorTile(x, y)) return true;

	//if there's enough space, recursively check midpoints
	if (distance(start, mid) > spacing) {
		if (isObstructed(start, mid, floor, spacing)) return true;
		else if (isObstructed(mid, end, floor, spacing)) return true;
	}
	return false;
}


void ChaseAI::move(DungeonFloor *floor, Vector3 &accel, Vector3 &pos, Vector3 &dest, float maxR, float minR) {

	//calculate vector from pos to dest and see if it is in range
	Vector3 dir(dest.x - pos.x, dest.y - pos.y, dest.z - pos.z);
	float dist = sqrt(dir.x * dir.x + dir.y * dir.y);

	//if in range and los isn't obstructed, then chase
	if (dist <= maxR && dist >= minR && !isObstructed(pos, dest, floor, 0.01f * TILE_SIZE)) {
		dir.normalize2d();
		dir *= moveAccel;
		accel.x = dir.x;
		accel.y = dir.y;
		accel.z = dir.z;
	}
	//otherwise, wander
	else {
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
}

MoveAI* ChaseAI::clone() {
	return new ChaseAI(*this);
}