#include "DungeonFloorGenerator.h"
#include "DungeonFloor.h"

DungeonFloorGenerator::DungeonFloorGenerator(int mapSize, int minRoomSize, float tileSize, Entity *player, int maxTries) : 
	mapSize(mapSize), minRoomSize(minRoomSize), tileSize(tileSize), player(player), maxTries(maxTries) {
	openTiles = std::set<Pair<int, int>>();

	tileMap = new unsigned char*[mapSize];
	for (int i = 0; i < mapSize; ++i) {
		tileMap[i] = new unsigned char[mapSize];
	}
}

bool DungeonFloorGenerator::recursiveSplitX(int x, int y, int width, int height) {
	//check if room is too small to split
	if (height <= 2 * minRoomSize) return false;

	int splitRange = height - 2 * minRoomSize;

	int splitAxis;
	int tries = 0;

	//attempt to choose an axis to split on that doesn't interfere with any doors
	do {
		if (tries > maxTries) return false;
		splitAxis = y + minRoomSize + (int)(rand() % splitRange);
		++tries;
	} while (tileMap[splitAxis][x - 1] == O || tileMap[splitAxis][x + width] == O);
	
	//we have to build a wall
	for (int i = x; i < x + width; ++i) {
		tileMap[splitAxis][i] = WE;
	}

	//create a random opening on the wall
	int door = (int)(rand() % width) + x;
	tileMap[splitAxis][door] = O;
	if (tileMap[splitAxis][door - 1] != NS && tileMap[splitAxis][door - 1] != NSFW && tileMap[splitAxis][door - 1] != N && tileMap[splitAxis][door - 1] != S)
		tileMap[splitAxis][door - 1] = W;
	if (tileMap[splitAxis][door + 1] != NS && tileMap[splitAxis][door + 1] != NSFE && tileMap[splitAxis][door + 1] != N && tileMap[splitAxis][door + 1] != S)
		tileMap[splitAxis][door + 1] = E;

	//recursively split
	if (!recursiveSplitY(x, y, width, splitAxis - y)) recursiveSplitX(x, y, width, splitAxis - y);
	if (!recursiveSplitY(x, splitAxis + 1, width, height - splitAxis + y - 1)) recursiveSplitX(x, splitAxis + 1, width, height - splitAxis + y - 1);

	return true;
}

bool DungeonFloorGenerator::recursiveSplitY(int x, int y, int width, int height) {
	//check if room is too small to split
	if (width <= 2 * minRoomSize) return false;

	int splitRange = width - 2 * minRoomSize;

	int splitAxis;
	int tries = 0;

	//attempt to choose an axis to split on that doesn't interfere with any doors
	do {
		if (tries > maxTries) return false;
		splitAxis = x + minRoomSize + (int)(rand() % splitRange);
		++tries;
	} while (tileMap[y - 1][splitAxis] == O || tileMap[y + height][splitAxis] == O);

	//we have to build a wall
	for (int i = y; i < y + height; ++i) {
		tileMap[i][splitAxis] = NS;
	}

	//create a random opening on the wall
	int door = (int)(rand() % height) + y;
	tileMap[door][splitAxis] = O;
	if (tileMap[door - 1][splitAxis] != WE && tileMap[door - 1][splitAxis] != WEFN && tileMap[door - 1][splitAxis] != W && tileMap[door - 1][splitAxis] != E)
		tileMap[door - 1][splitAxis] = N;
	if (tileMap[door + 1][splitAxis] != WE && tileMap[door + 1][splitAxis] != WEFS && tileMap[door + 1][splitAxis] != W && tileMap[door + 1][splitAxis] != E)
		tileMap[door + 1][splitAxis] = S;

	//recursively split
	if (!recursiveSplitX(x, y, splitAxis - x, height)) recursiveSplitY(x, y, splitAxis - x, height);
	if (!recursiveSplitX(splitAxis + 1, y, width - splitAxis + x - 1, height)) recursiveSplitY(splitAxis + 1, y, width - splitAxis + x - 1, height);

	return true;
}


void DungeonFloorGenerator::generateMap() {

	//init corners
	tileMap[0][0] = SEFNW;
	tileMap[0][mapSize - 1] = SWFNE;
	tileMap[mapSize - 1][0] = NEFSW;
	tileMap[mapSize - 1][mapSize - 1] = NWFSE;

	//init otpe and bottom rows
	for (int x = 1; x < mapSize-1; ++x) {
		tileMap[0][x] = WEFN;
		tileMap[mapSize - 1][x] = WEFS;
	}

	//init the rest
	for (int y = 1; y < mapSize - 1; ++y) {
		tileMap[y][0] = NSFW;
		tileMap[y][mapSize - 1] = NSFE;
		for (int x = 1; x < mapSize - 1; ++x) {
			tileMap[y][x] = O;
		}
	}

	//split!
	recursiveSplitX(1, 1, mapSize - 2, mapSize - 2);
}

void DungeonFloorGenerator::findOpenTiles() {
	openTiles.clear();
	for (int y = 0; y < mapSize; ++y) {
		for (int x = 0; x < mapSize; ++x) {
			if (tileMap[y][x] == O)
				openTiles.insert(Pair<int, int>(x, y));
		}
	}
}

bool DungeonFloorGenerator::spawnEntity(Entity *entity) {
	if (openTiles.size() == 0) return false;

	//select random open tile
	int index = (int)(rand() % openTiles.size());
	Pair<int, int> coords(0, 0);
	std::set<Pair<int, int>>::const_iterator itr(openTiles.begin());
	advance(itr, index);
	coords.x = itr->x;
	coords.y = itr->y;

	//place entity on tile and remove tile from list
	tileToWorldCoordinates(coords.x, coords.y, entity->position.x, entity->position.y, mapSize);
	openTiles.erase(itr);

	//also remove any surrounding tiles, if they exist !!!!!! MIGHT NOT WORK !!!!!!!
	openTiles.erase(Pair<int, int>(coords.x + 1, coords.y));
	openTiles.erase(Pair<int, int>(coords.x - 1, coords.y));
	openTiles.erase(Pair<int, int>(coords.x, coords.y + 1));
	openTiles.erase(Pair<int, int>(coords.x, coords.y - 1));
	openTiles.erase(Pair<int, int>(coords.x + 1, coords.y + 1));
	openTiles.erase(Pair<int, int>(coords.x + 1, coords.y - 1));
	openTiles.erase(Pair<int, int>(coords.x - 1, coords.y + 1));
	openTiles.erase(Pair<int, int>(coords.x - 1, coords.y - 1));

	return true;
}

DungeonFloor* DungeonFloorGenerator::generate(const char *spriteSheetName, int numx, int numy) {
	generateMap();
	//fix tile connections
	findOpenTiles();
	//spawn exit
	//spawn chests
	//spawn enemies
	//delete tiles in radius form exit tile
	spawnEntity(player); //if no suitable, replace enemy with player
	//spawn entrance tile
	int x, y;
	worldToTileCoordinates(player->position.x, player->position.y, x, y, mapSize);
	tileMap[y][x] = enter;

	DungeonFloor *floor = new DungeonFloor(mapSize, tileSize, tileMap, spriteSheetName, numx, numy, player);
	return floor;
}