#ifndef MKL_UTIL
#define MKL_UTIL

#include "ShaderProgram.h"

#define FIXED_TIMESTEP 0.0066666f
#define MAX_TIMESTEPS 8
#define TILE_SIZE 0.5f

class DungeonFloor;

class Vector3 {
public:
	Vector3() { Vector3(0, 0, 0); }
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	float x;
	float y;
	float z;

};

GLuint LoadTexture(const char *image_path);

void DrawSpriteSheetSprite(ShaderProgram *program, int index, int spriteCountX, int spriteCountY, GLuint textureID, float tileSize);

float lerp(float v0, float v1, float t);

void worldToTileCoordinates(float worldX, float worldY, int &gridX, int &gridY, DungeonFloor &floor);

void tileToWorldCoordinates(int gridX, int gridY, float &worldX, float &worldY, DungeonFloor &floor);

#endif MKL_UTIL