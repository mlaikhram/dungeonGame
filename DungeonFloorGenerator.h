#ifndef MKL_DUNGEONFLOORGENERATOR
#define MKL_DUNGEONFLOORGENERATOR

#include <set>
#include "Util.h"
#include "Entity.h"

class DungeonFloorGenerator {
public:
	DungeonFloorGenerator(int mapSize, int minRoomSize, float tileSize, Entity *player, int maxTries = 10);

	//x: x pos of the top left FLOOR TILE
	//y: y pos of the top left FLOOR TILE
	//width/height of room EXCLUDING BORDERING WALL TILES
	bool recursiveSplitX(int x, int y, int width, int height);
	bool recursiveSplitY(int x, int y, int width, int height);
	//bool recursiveSplitY(int x, int y, int width, int height);
	void generateMap();
	void fixTileConnections();
	bool floorTile(int x, int y);
	void findOpenTiles();
	void randomizeOpenTiles(int maxTiles = 20);
	void deleteOpenTilesR(int x, int y, int radius);
	int countNearbyObstructions(int x, int y);
	bool spawnEntity(Entity *entity, int radius = 0, int maxObstructions = 8);

	DungeonFloor* generate(const char *spriteSheetName, const char *miniMapSheetName, int numx, int numy);

private:
	int mapSize;
	int minRoomSize;
	float tileSize;
	unsigned char **tileMap;
	Entity *player;
	int maxTries;
	std::set<Pair<int, int>> openTiles;
};

#endif MKL_DUNGEONFLOORGENERATOR