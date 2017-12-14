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
#include "Enemy.h"
#include "Player.h"

class Enemy;

class DungeonFloor {
public:
	DungeonFloor(int mapSize, float tileSize, unsigned char **_tileMap, const char *spriteSheetName, const char *miniMapSheetName, int numx, int numy, Player *player, std::vector<Chest> &chests = std::vector<Chest>(), std::list<Enemy> &enemies = std::list<Enemy>());
	~DungeonFloor();
	bool testOutOfBounds(int gridX, int gridY);
	bool floorTile(int x, int y); 
	void eliminateEncountered();
	void mapCollision(Entity &entity, ShaderProgram *program);
	bool tileCollision(ShaderProgram *program, int index);
	bool tileCollision(ShaderProgram *program, int x, int y);
	void update(ShaderProgram *program, float time, int maxTries = 10);
	void draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix);

	void add(Enemy &e);
	void add(Chest &c);

	bool isEncountered() const;
	std::list<Enemy>::iterator getEncountered() const;
	int getMapSize() const;
	float getTileSize() const;
	unsigned char** getTileMap() const;
	GLuint getSpriteSheet() const;
	std::vector<Chest>& getChests();
	std::list<Enemy>& getEnemies();
	void updateTiles(unsigned char **t);

	void setSpriteSheet(const char* name);

private:
	int mapSize;
	float tileSize;
	unsigned char **tileMap;
	bool **miniMap;
	GLuint spriteSheet;
	GLuint miniMapSheet;
	int numx;
	int numy;
	Player *player; //shallow
	std::vector<Chest> chests;
	std::list<Enemy> enemies;
	std::list<Enemy>::iterator encountered;
	//int collectedMoney;

};


#endif MKL_DUNGEONFLOOR