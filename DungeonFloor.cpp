#include "Util.h"
#include "DungeonFloor.h"

DungeonFloor::DungeonFloor(int mapSize, float tileSize, unsigned char **_tileMap, const char *spriteSheetName, int numx, int numy, Entity *player, std::vector<Chest> chests) : 
	mapSize(mapSize), tileSize(tileSize), numx(numx), numy(numy), player(player), chests(chests) {
	tileMap = new unsigned char*[mapSize];
	for (int i = 0; i < mapSize; ++i) {
		tileMap[i] = new unsigned char[mapSize];
	}
	for (int y = 0; y < mapSize; ++y) {
		for (int x = 0; x < mapSize; ++x) {
			tileMap[y][x] = _tileMap[y][x];
		}
	}
	spriteSheet = LoadTexture(spriteSheetName);
}

bool DungeonFloor::testOutOfBounds(int gridX, int gridY) {
	if (gridX < 0 || gridX >= mapSize || gridY < 0 || gridY >= mapSize) {
		return true;
	}
	return false;
}

bool DungeonFloor::floorTile(int x, int y) {
	return tileMap[y][x] == O1 || tileMap[y][x] == O2 || tileMap[y][x] == O3 || tileMap[y][x] == O4 || tileMap[y][x] == O5 || tileMap[y][x] == X || tileMap[y][x] == enter;
}

void DungeonFloor::mapCollision(Entity &entity, ShaderProgram *program) {
	int gridX, gridY;
	float offset = (tileSize - entity.size) / 2;

	//check left
	worldToTileCoordinates(entity.position.x + offset, entity.position.y - 0.008f - offset, gridX, gridY, mapSize);
	if (testOutOfBounds(gridX, gridY)) {
		//handleOOB(entity);
		return;
	}
	if (!(gridX < 0 || gridX > mapSize || gridY < 0 || gridY > mapSize) && !floorTile(gridX, gridY))
	{
		entity.position.x += 0.008f;
		entity.velocity.x = 0.0f;
		//entity.acceleration.x = 0;
		entity.collidedLeft = true;
	}
	worldToTileCoordinates(entity.position.x + offset, entity.position.y - entity.size + 0.008f - offset, gridX, gridY, mapSize);
	if (testOutOfBounds(gridX, gridY)) {
		//handleOOB(entity);
		return;
	}
	if (!(gridX < 0 || gridX > mapSize || gridY < 0 || gridY > mapSize) && !floorTile(gridX, gridY))
	{
		entity.position.x += 0.008f;
		entity.velocity.x = 0.0f;
		//entity.acceleration.x = 0;
		entity.collidedLeft = true;
	}
	//check right
	worldToTileCoordinates(entity.position.x + entity.size + offset, entity.position.y - 0.008f - offset, gridX, gridY, mapSize);
	if (testOutOfBounds(gridX, gridY)) {
		//handleOOB(entity);
		return;
	}
	if (!(gridX < 0 || gridX > mapSize || gridY < 0 || gridY > mapSize) && !floorTile(gridX, gridY))
	{
		entity.position.x -= 0.008f;
		entity.velocity.x = 0.0f;
		//entity.acceleration.x = 0;
		entity.collidedRight = true;
	}
	worldToTileCoordinates(entity.position.x + entity.size + offset, entity.position.y - entity.size + 0.008f - offset, gridX, gridY, mapSize);
	if (testOutOfBounds(gridX, gridY)) {
		//handleOOB(entity);
		return;
	}
	if (!(gridX < 0 || gridX > mapSize || gridY < 0 || gridY > mapSize) && !floorTile(gridX, gridY))
	{
		entity.position.x -= 0.008f;
		entity.velocity.x = 0.0f;
		//entity.acceleration.x = 0;
		entity.collidedRight = true;
	}
	//check bottom
	worldToTileCoordinates(entity.position.x + 0.008f + offset, entity.position.y - entity.size - offset, gridX, gridY, mapSize);
	if (testOutOfBounds(gridX, gridY)) {
		//handleOOB(entity);
		return;
	}
	if (!(gridX < 0 || gridX > mapSize || gridY < 0 || gridY > mapSize) && !floorTile(gridX, gridY))
	{
		entity.position.y += 0.008f;
		entity.velocity.y = 0.0f;
		//entity.acceleration.y = 0;
		entity.collidedBottom = true;
	}
	worldToTileCoordinates(entity.position.x + entity.size - 0.008f + offset, entity.position.y - entity.size - offset, gridX, gridY, mapSize);
	if (testOutOfBounds(gridX, gridY)) {
		//handleOOB(entity);
		return;
	}
	if (!(gridX < 0 || gridX > mapSize || gridY < 0 || gridY > mapSize) && !floorTile(gridX, gridY))
	{
		entity.position.y += 0.008f;
		entity.velocity.y = 0.0f;
		//entity.acceleration.y = 0;
		entity.collidedBottom = true;
	}
	//check top
	worldToTileCoordinates(entity.position.x + 0.008f + offset, entity.position.y - offset, gridX, gridY, mapSize);
	if (testOutOfBounds(gridX, gridY)) {
		//handleOOB(entity);
		return;
	}
	if (!(gridX < 0 || gridX > mapSize || gridY < 0 || gridY > mapSize) && !floorTile(gridX, gridY))
	{
		entity.position.y -= 0.008f;
		entity.velocity.y = 0.0f;
		//entity.acceleration.y = 0;
		entity.collidedTop = true;
	}
	worldToTileCoordinates(entity.position.x + entity.size - 0.008f + offset, entity.position.y - offset, gridX, gridY, mapSize);
	if (testOutOfBounds(gridX, gridY)) {
		//handleOOB(entity);
		return;
	}
	if (!(gridX < 0 || gridX > mapSize || gridY < 0 || gridY > mapSize) && !floorTile(gridX, gridY))
	{
		entity.position.y -= 0.008f;
		entity.velocity.y = 0.0f;
		//entity.acceleration.y = 0;
		entity.collidedTop = true;
	}
}

bool DungeonFloor::tileCollision(ShaderProgram *program, int index) {
	int gridX, gridY;
	float offset = (tileSize - player->size) / 2;

	//check left
	worldToTileCoordinates(player->position.x + offset, player->position.y - 0.008f - offset, gridX, gridY, mapSize);
	if (testOutOfBounds(gridX, gridY)) {
		//handleOOB(entity);
		return false;
	}
	if (!(gridX < 0 || gridX > mapSize || gridY < 0 || gridY > mapSize) && tileMap[gridY][gridX] == index)
	{
		return true;
	}
	worldToTileCoordinates(player->position.x + offset, player->position.y - player->size + 0.008f - offset, gridX, gridY, mapSize);
	if (testOutOfBounds(gridX, gridY)) {
		//handleOOB(entity);
		return false;
	}
	if (!(gridX < 0 || gridX > mapSize || gridY < 0 || gridY > mapSize) && tileMap[gridY][gridX] == index)
	{
		return true;
	}
	//check right
	worldToTileCoordinates(player->position.x + player->size + offset, player->position.y - 0.008f - offset, gridX, gridY, mapSize);
	if (testOutOfBounds(gridX, gridY)) {
		//handleOOB(entity);
		return false;
	}
	if (!(gridX < 0 || gridX > mapSize || gridY < 0 || gridY > mapSize) && tileMap[gridY][gridX] == index)
	{
		return true;
	}
	worldToTileCoordinates(player->position.x + player->size + offset, player->position.y - player->size + 0.008f - offset, gridX, gridY, mapSize);
	if (testOutOfBounds(gridX, gridY)) {
		//handleOOB(entity);
		return false;
	}
	if (!(gridX < 0 || gridX > mapSize || gridY < 0 || gridY > mapSize) && tileMap[gridY][gridX] == index)
	{
		return true;
	}
	//check bottom
	worldToTileCoordinates(player->position.x + 0.008f + offset, player->position.y - player->size - offset, gridX, gridY, mapSize);
	if (testOutOfBounds(gridX, gridY)) {
		//handleOOB(entity);
		return false;
	}
	if (!(gridX < 0 || gridX > mapSize || gridY < 0 || gridY > mapSize) && tileMap[gridY][gridX] == index)
	{
		return true;
	}
	worldToTileCoordinates(player->position.x + player->size - 0.008f + offset, player->position.y - player->size - offset, gridX, gridY, mapSize);
	if (testOutOfBounds(gridX, gridY)) {
		//handleOOB(entity);
		return false;
	}
	if (!(gridX < 0 || gridX > mapSize || gridY < 0 || gridY > mapSize) && tileMap[gridY][gridX] == index)
	{
		return true;
	}
	//check top
	worldToTileCoordinates(player->position.x + 0.008f + offset, player->position.y - offset, gridX, gridY, mapSize);
	if (testOutOfBounds(gridX, gridY)) {
		//handleOOB(entity);
		return false;
	}
	if (!(gridX < 0 || gridX > mapSize || gridY < 0 || gridY > mapSize) && tileMap[gridY][gridX] == index)
	{
		return true;
	}
	worldToTileCoordinates(player->position.x + player->size - 0.008f + offset, player->position.y - offset, gridX, gridY, mapSize);
	if (testOutOfBounds(gridX, gridY)) {
		//handleOOB(entity);
		return false;
	}
	if (!(gridX < 0 || gridX > mapSize || gridY < 0 || gridY > mapSize) && tileMap[gridY][gridX] == index)
	{
		return true;
	}
	return false;
}

bool DungeonFloor::tileCollision(ShaderProgram *program, int x, int y) {
	int gridX, gridY;
	float offset = (tileSize - player->size) / 2;

	//check left
	worldToTileCoordinates(player->position.x + offset, player->position.y - 0.008f - offset, gridX, gridY, mapSize);
	if (x == gridX && y == gridY) return true;
	worldToTileCoordinates(player->position.x + offset, player->position.y - player->size + 0.008f - offset, gridX, gridY, mapSize);
	if (x == gridX && y == gridY) return true;
	//check right
	worldToTileCoordinates(player->position.x + player->size + offset, player->position.y - 0.008f - offset, gridX, gridY, mapSize);
	if (x == gridX && y == gridY) return true;
	worldToTileCoordinates(player->position.x + player->size + offset, player->position.y - player->size + 0.008f - offset, gridX, gridY, mapSize);
	if (x == gridX && y == gridY) return true;
	//check bottom
	worldToTileCoordinates(player->position.x + 0.008f + offset, player->position.y - player->size - offset, gridX, gridY, mapSize);
	if (x == gridX && y == gridY) return true;
	worldToTileCoordinates(player->position.x + player->size - 0.008f + offset, player->position.y - player->size - offset, gridX, gridY, mapSize);
	if (x == gridX && y == gridY) return true;
	//check top
	worldToTileCoordinates(player->position.x + 0.008f + offset, player->position.y - offset, gridX, gridY, mapSize);
	if (x == gridX && y == gridY) return true;
	worldToTileCoordinates(player->position.x + player->size - 0.008f + offset, player->position.y - offset, gridX, gridY, mapSize);
	if (x == gridX && y == gridY) return true;
	return false;
}

void DungeonFloor::update(ShaderProgram *program, float time, int maxTries) {
	int tries = 0;
	for (int i = 0; i < chests.size(); ++i) {
		while (player->collidesWith(chests[i])) {
			if (tries > maxTries) break;
			player->nudge(chests[i], 0.0f);
			++tries;
		}
	}
	mapCollision(*player, program);
	for (int i = 0; i < chests.size(); ++i) {
		chests[i].update(program, time);
		mapCollision(chests[i], program);
	}
}

void DungeonFloor::draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix) {

	for (int y = 0; y < mapSize; ++y) {
		for (int x = 0; x < mapSize; ++x) {
			modelMatrix.identity();
			modelMatrix.Translate(float(x)*tileSize, (mapSize - float(y) - 1.0f)*tileSize, 0.0f);
			program->setModelMatrix(modelMatrix);
			program->setProjectionMatrix(projectionMatrix);
			program->setViewMatrix(viewMatrix);
			DrawSpriteSheetSprite(program, tileMap[y][x], numx, numy, spriteSheet, tileSize);
		}
	}

	for (Chest &chest : chests)
		chest.draw(program, projectionMatrix, modelMatrix, viewMatrix);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int DungeonFloor::getMapSize() const { return mapSize; }
float DungeonFloor::getTileSize() const { return tileSize; }
unsigned char** DungeonFloor::getTileMap() const { return tileMap; }
GLuint DungeonFloor::getSpriteSheet() const { return spriteSheet; }
std::vector<Chest>& DungeonFloor::getChests() { return chests; }

void DungeonFloor::setSpriteSheet(const char* name) { spriteSheet = LoadTexture(name); }