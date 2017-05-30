#ifndef MKL_UTIL
#define MKL_UTIL

#include "ShaderProgram.h"

#define FIXED_TIMESTEP 0.0066666f
#define MAX_TIMESTEPS 8
#define TILE_SIZE 0.5f

enum maptiles { O, WE, WEFS, WEFN, NS, NSFE, NSFW, NSWE, NSW, NSWFE, NSE, NSEFW, SWE, SWEFN, NWE, NWEFS, NWFSE, NW, NEFSW, NE, SWFNE, SW, SEFNW, SE, N, S, W, E, enter, X, chest1 };

class DungeonFloor;

class Vector3 {
public:
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	void normalize2d() {
		float mag = sqrt(x*x + y*y);
		if (mag != 0) {
			x /= mag;
			y /= mag;
		}
	}
	float x;
	float y;
	float z;

};

template<class obj1, class obj2>
class Pair {
public:
	Pair(obj1 x, obj2 y) : x(x), y(y) {}
	bool operator==(Pair<obj1, obj2> &rhs) const { return (x == rhs.x && y == rhs.y); }
	bool operator<(const Pair<obj1, obj2> &rhs) const { return ((x < rhs.x) || (x == rhs.x && y < rhs.y)); }
	obj1 x;
	obj2 y;
};

GLuint LoadTexture(const char *image_path);

void DrawSpriteSheetSprite(ShaderProgram *program, int index, int spriteCountX, int spriteCountY, GLuint textureID, float tileSize);

float lerp(float v0, float v1, float t);

void worldToTileCoordinates(float worldX, float worldY, int &gridX, int &gridY, int mapSize);

void tileToWorldCoordinates(int gridX, int gridY, float &worldX, float &worldY, int mapSize);

#endif MKL_UTIL