#ifndef MKL_DUNGEONFLOOR
#define MKL_DUNGEONFLOOR

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "Matrix.h"
#include "ShaderProgram.h"
#include "Entity.h"

class DungeonFloor {
public:
	DungeonFloor(int mapSize, float tileSize, unsigned char **_tileMap, const char *spriteSheetName, int numx, int numy, Entity *player);
	DungeonFloor(int mapSize, float tileSize, unsigned char **_tileMap, GLuint spriteSheet, int numx, int numy, Entity *player);

	bool testOutOfBounds(int gridX, int gridY);
	void mapCollision(Entity &entity, ShaderProgram *program);
	void draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix);

	int getMapSize() const;
	float getTileSize() const;
	unsigned char** getTileMap() const;
	GLuint getSpriteSheet() const;

	void setSpriteSheet(const char* name);

private:
	int mapSize;
	float tileSize;
	unsigned char **tileMap;
	GLuint spriteSheet;
	int numx;
	int numy;
	Entity *player;
};


#endif MKL_DUNGEONFLOOR