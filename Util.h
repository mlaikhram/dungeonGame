#ifndef MKL_UTIL
#define MKL_UTIL

#include "ShaderProgram.h"

#define FIXED_TIMESTEP 0.0066666f
#define MAX_TIMESTEPS 8

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

#endif MKL_UTIL