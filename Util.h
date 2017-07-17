#ifndef MKL_UTIL
#define MKL_UTIL

#ifdef _WINDOWS
#include <GL/glew.h>
#endif
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "ShaderProgram.h"

#define FIXED_TIMESTEP 0.0166666f
#define MAX_TIMESTEPS 6
#define TILE_SIZE 0.5f
#define PI 3.141592653589793238462643383279f

enum alignment { LEFT_JUST, CENTERED, RIGHT_JUST };
enum states { STATE_MAINMENU, STATE_DUNGEON, STATE_ENCOUNTER, STATE_END };
enum maptiles { WE, WEFS, WEFN, NS, NSFE, NSFW, NSWE, NSW, NSWFE, NSE,
				NSEFW, SWE, SWEFN, NWE, NWEFS, NWFSE, NW, NEFSW, NE, SWFNE,
				SW, SEFNW, SE, N, S, W, E, chestc, chesto, enter,
				X, O1, O2, O3, O4, O5, playerm };

class DungeonFloor;

class Vector3 {
public:
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	bool isZero() {
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}
	void normalize2d() {
		float mag = sqrt(x*x + y*y);
		if (mag != 0) {
			x /= mag;
			y /= mag;
		}
	}
	void operator*=(float rhs) {
		x = rhs * x;
		y = rhs * y;
		z = rhs * z;
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

float distance(Vector3 a, Vector3 b);

#endif MKL_UTIL