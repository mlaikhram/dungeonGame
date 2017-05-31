#ifndef MKL_DUNGEONFLOOR
#define MKL_DUNGEONFLOOR

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <vector>
#include "Matrix.h"
#include "ShaderProgram.h"
#include "Entity.h"
#include "Chest.h"

class DungeonFloor {
public:
	DungeonFloor(int mapSize, float tileSize, unsigned char **_tileMap, const char *spriteSheetName, int numx, int numy, Entity *player, std::vector<Chest> chests = std::vector<Chest>());

	bool testOutOfBounds(int gridX, int gridY);
	bool floorTile(int x, int y);
	void mapCollision(Entity &entity, ShaderProgram *program);
	bool tileCollision(ShaderProgram *program, int index);
	bool tileCollision(ShaderProgram *program, int x, int y);
	void update(ShaderProgram *program, float time, int maxTries = 10);
	void draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix);

	int getMapSize() const;
	float getTileSize() const;
	unsigned char** getTileMap() const;
	GLuint getSpriteSheet() const;
	std::vector<Chest>& getChests();

	void setSpriteSheet(const char* name);

private:
	int mapSize;
	float tileSize;
	unsigned char **tileMap;
	GLuint spriteSheet;
	int numx;
	int numy;
	Entity *player;
	std::vector<Chest> chests;

};


#endif MKL_DUNGEONFLOOR