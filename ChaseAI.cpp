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

//void ChaseAI::move(DungeonFloor *floor, Vector3 &accel, Vector3 &pos, Vector3 &dest, float maxR, float minR) {
//
//	//calculate vector from pos to dest and see if it is in range
//	Vector3 dir(dest.x - pos.x, dest.y - pos.y, dest.z - pos.z);
//	float dist = sqrt(dir.x * dir.x + dir.y * dir.y);
//	bool obstructed = false;
//
//	if (dist <= maxR && dist >= minR) {
//		float m = (dest.y - pos.y) / (dest.x - pos.x);
//
//		Vector3 step;
//		Vector3 end;
//
//		//determine which point is farther right to use as the endpoint
//		if (dest.x > pos.x) {
//			step.x = pos.x;
//			step.y = pos.y;
//			end.x = dest.x;
//			end.y = dest.y;
//		}
//		else {
//			step.x = dest.x;
//			step.y = dest.y;
//			end.x = pos.x;
//			end.y = pos.y;
//		}
//		//step along the segment between pos and dest looking for obstructions
//		//if both points share an xcor, then do the same process for the ycor
//		if (step.x == end.x) {
//			if (dest.y > pos.y) {
//				step.x = pos.x;
//				step.y = pos.y;
//				end.x = dest.x;
//				end.y = dest.y;
//			}
//			else {
//				step.x = dest.x;
//				step.y = dest.y;
//				end.x = pos.x;
//				end.y = pos.y;
//			}
//			while (step.y < end.y) {
//				int x, y;
//				worldToTileCoordinates(step.x, step.y, x, y, floor->getMapSize());
//				if (!floor->floorTile(x, y)) {
//					obstructed = true;
//					break;
//				}
//				float dy = TILE_SIZE / 5;
//				step.y += dy;
//			}
//		}
//		else {
//			while (step.x < end.x) {
//				int x, y;
//				worldToTileCoordinates(step.x, step.y, x, y, floor->getMapSize());
//				if (!floor->floorTile(x, y)) {
//					obstructed = true;
//					break;
//				}
//				float dx = TILE_SIZE / 5;
//				step.x += dx;
//				step.y += dx * m;
//			}
//		}
//	}
//	else {
//		obstructed = true;
//	}
//	//if you see the dest, chase it
//	if (!obstructed) {
//		dir.normalize2d();
//		dir *= moveAccel;
//		accel.x = dir.x;
//		accel.y = dir.y;
//		accel.z = dir.z;
//	}
//	//otherwise, wander
//	else {
//		if (timer == 0.0f) {
//			if (accel.isZero())
//				wander(accel);
//			else {
//				accel.x = 0.0f;
//				accel.y = 0.0f;
//				accel.z = 0.0f;
//			}
//		}
//	}
//}