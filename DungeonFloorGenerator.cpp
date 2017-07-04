#include <vector>
#include "DungeonFloorGenerator.h"
#include "DungeonFloor.h"
#include "Enemy.h"
#include "WanderAI.h"
#include "ChaseAI.h"

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
	} while (tileMap[splitAxis][x - 1] == O1 || tileMap[splitAxis][x + width] == O1);
	
	//we have to build a wall
	for (int i = x; i < x + width; ++i) {
		tileMap[splitAxis][i] = WE;
	}

	//create a random opening on the wall
	int door = (int)(rand() % width) + x;
	tileMap[splitAxis][door] = O1;
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
	} while (tileMap[y - 1][splitAxis] == O1 || tileMap[y + height][splitAxis] == O1);

	//we have to build a wall
	for (int i = y; i < y + height; ++i) {
		tileMap[i][splitAxis] = NS;
	}

	//create a random opening on the wall
	int door = (int)(rand() % height) + y;
	tileMap[door][splitAxis] = O1;
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

	//init top and bottom rows
	for (int x = 1; x < mapSize-1; ++x) {
		tileMap[0][x] = WEFN;
		tileMap[mapSize - 1][x] = WEFS;
	}

	//init the rest
	for (int y = 1; y < mapSize - 1; ++y) {
		tileMap[y][0] = NSFW;
		tileMap[y][mapSize - 1] = NSFE;
		for (int x = 1; x < mapSize - 1; ++x) {
			tileMap[y][x] = O1;
		}
	}

	//split!
	if (rand() % 2 == 0)
		recursiveSplitX(1, 1, mapSize - 2, mapSize - 2);
	else
		recursiveSplitY(1, 1, mapSize - 2, mapSize - 2);
}

void DungeonFloorGenerator::fixTileConnections() {
	//fix border tiles
	for (int x = 1; x < mapSize - 2; ++x) {
		if (!floorTile(x, 1)) tileMap[0][x] = SWEFN;
		if (!floorTile(x, mapSize - 2)) tileMap[mapSize - 1][x] = NWEFS;
	}
	for (int y = 1; y < mapSize - 2; ++y) {
		if (!floorTile(1, y)) tileMap[y][0] = NSEFW;
		if (!floorTile(mapSize - 2, y)) tileMap[y][mapSize - 1] = NSWFE;
	}

	//fix all inner connections
	for (int x = 1; x < mapSize - 2; ++x) {
		for (int y = 1; y < mapSize - 2; ++y) {
			if (!floorTile(x, y) && !floorTile(x, y - 1) && !floorTile(x, y + 1) && !floorTile(x - 1, y) && !floorTile(x + 1, y))
				tileMap[y][x] = NSWE;
			else if (!floorTile(x, y) && !floorTile(x, y - 1) && !floorTile(x, y + 1) && !floorTile(x - 1, y))
				tileMap[y][x] = NSW;
			else if (!floorTile(x, y) && !floorTile(x, y - 1) && !floorTile(x, y + 1) && !floorTile(x + 1, y))
				tileMap[y][x] = NSE;
			else if (!floorTile(x, y) && !floorTile(x, y - 1) && !floorTile(x - 1, y) && !floorTile(x + 1, y))
				tileMap[y][x] = NWE;
			else if (!floorTile(x, y) && !floorTile(x, y + 1) && !floorTile(x - 1, y) && !floorTile(x + 1, y))
				tileMap[y][x] = SWE;
			else if (!floorTile(x, y) && !floorTile(x, y - 1) && !floorTile(x - 1, y))
				tileMap[y][x] = NW;
			else if (!floorTile(x, y) && !floorTile(x, y - 1) && !floorTile(x + 1, y))
				tileMap[y][x] = NE;
			else if (!floorTile(x, y) && !floorTile(x, y + 1) && !floorTile(x - 1, y))
				tileMap[y][x] = SW;
			else if (!floorTile(x, y) && !floorTile(x, y + 1) && !floorTile(x + 1, y))
				tileMap[y][x] = SE;
		}
	}
}

bool DungeonFloorGenerator::floorTile(int x, int y) {
	return tileMap[y][x] == O1 || tileMap[y][x] == O2 || tileMap[y][x] == O3 || tileMap[y][x] == O4 || tileMap[y][x] == O5 || tileMap[y][x] == X || tileMap[y][x] == enter;
}

void DungeonFloorGenerator::findOpenTiles() {
	openTiles.clear();
	for (int y = 0; y < mapSize; ++y) {
		for (int x = 0; x < mapSize; ++x) {
			if (floorTile(x, y))
				openTiles.insert(Pair<int, int>(x, y));
		}
	}
}

void DungeonFloorGenerator::randomizeOpenTiles(int maxTiles) {
	if (openTiles.size() == 0) return;
	int alts[4] = { O2, O3, O4, O5 };

	Pair<int, int> coords(0, 0);
	std::set<Pair<int, int>>::const_iterator itr;

	for (int i = 0; i < maxTiles; ++i) {
		//select random open tile
		itr = openTiles.begin();
		int index = (int)(rand() % openTiles.size());
		advance(itr, index);
		tileMap[itr->y][itr->x] = alts[(int)(rand() % 4)];
	}
}

void DungeonFloorGenerator::deleteOpenTilesR(int x, int y, int radius) {
	for (int i = x - radius; i <= x + radius; ++i) {
		for (int j = y - radius; j <= y + radius; ++j) {
			if (openTiles.find(Pair<int, int>(i, j)) != openTiles.end())
				openTiles.erase(openTiles.find(Pair<int, int>(i, j)));
		}
	}
}

int DungeonFloorGenerator::countNearbyObstructions(int x, int y) {
	int count = 0;
	for (int i = x - 1; i <= x + 1; ++i) {
		for (int j = y - 1; j <= y + 1; ++j) {
			if (!floorTile(i, j)) ++count;
		}
	}
	return count;
}

bool DungeonFloorGenerator::spawnEntity(Entity *entity, int radius, int maxObstructions) {
	if (openTiles.size() == 0) return false;

	Pair<int, int> coords(0, 0);
	std::set<Pair<int, int>>::const_iterator itr;
	int tries = 0;

	//select random open tile with the obstruction requirements
	do {
		if (tries > maxTries) return false;
		itr = openTiles.begin();
		int index = (int)(rand() % openTiles.size());
		advance(itr, index);
		coords.x = itr->x;
		coords.y = itr->y;
		++tries;
	} while (countNearbyObstructions(coords.x, coords.y) > maxObstructions);

	//place entity on tile and remove tile from list
	tileToWorldCoordinates(coords.x, coords.y, entity->position.x, entity->position.y, mapSize);

	//also remove any surrounding tiles, if they exist
	if (radius <= 0)
		openTiles.erase(itr);
	else
		deleteOpenTilesR(coords.x, coords.y, radius);

	return true;
}

DungeonFloor* DungeonFloorGenerator::generate(const char *spriteSheetName, const char *miniMapSheetName, int numx, int numy) {
	generateMap();
	fixTileConnections();
	findOpenTiles();
	randomizeOpenTiles(mapSize * mapSize * 0.01);
	//spawn exit
	//select random open tile
	int index = (int)(rand() % openTiles.size());
	Pair<int, int> exitCoords(0, 0);
	std::set<Pair<int, int>>::const_iterator itr(openTiles.begin());
	advance(itr, index);
	exitCoords.x = itr->x;
	exitCoords.y = itr->y;
	tileMap[exitCoords.y][exitCoords.x] = X;
	openTiles.erase(itr);
	//spawn chests (not REAL)
	std::vector<Chest> chests = std::vector<Chest>();
	std::ofstream ofs("output.txt");
	for (int i = 0; i < 10; ++i) {
		Chest *chest = new Chest("tilemap_dungeon1.png", chestc, 10, 10, Vector3(), 0.7f * TILE_SIZE);
		if (spawnEntity(chest, 0, 1)) {
			int gridX, gridY;
			worldToTileCoordinates(chest->position.x, chest->position.y, gridX, gridY, mapSize);
			//ofs << "count: " << countNearbyObstructions(gridX, gridY) << std::endl;
			chests.push_back(*chest);
			tileMap[gridY][gridX] = O1;
		}
		else
			delete chest;
	}
	//spawn enemies (not REAL)
	std::vector<Enemy> enemies = std::vector<Enemy>();
	MoveAI *wander = new ChaseAI(5.0f);
	for (int i = 0; i < 20; ++i) {
		Enemy *enemy = new Enemy("tiles.png", 52, 20, 20, wander, player, Vector3(), 0.75 * TILE_SIZE);
		if (spawnEntity(enemy, 1)) {
			int gridX, gridY;
			worldToTileCoordinates(enemy->position.x, enemy->position.y, gridX, gridY, mapSize);
			//ofs << "count: " << countNearbyObstructions(gridX, gridY) << std::endl;
			enemies.push_back(*enemy);
			//tileMap[gridY][gridX] = O1;
		}
		else
			delete enemy;
	}
	//delete tiles in radius form exit tile
	deleteOpenTilesR(exitCoords.x, exitCoords.y, 2.5 * minRoomSize);

	//if no suitable, replace enemy with player
	if (!spawnEntity(player)) {
		player->position = enemies[enemies.size() - 1].position;
		enemies.pop_back();
	}
	//spawn entrance tile
	int x, y;
	worldToTileCoordinates(player->position.x, player->position.y, x, y, mapSize);
	tileMap[y][x] = enter;

	DungeonFloor *floor = new DungeonFloor(mapSize, tileSize, tileMap, spriteSheetName, miniMapSheetName, numx, numy, player, chests, enemies);
	return floor;
}