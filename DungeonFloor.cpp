#include "Util.h"
#include "DungeonFloor.h"

DungeonFloor::DungeonFloor(int mapSize, float tileSize, unsigned char **_tileMap, const char *spriteSheetName, const char *miniMapSheetName, int numx, int numy, Player *player, std::vector<Chest> &chests, std::list<Enemy> &enemies) :
	mapSize(mapSize), tileSize(tileSize), numx(numx), numy(numy), player(player), chests(chests), enemies(enemies) {

	encountered = this->enemies.end();

	tileMap = new unsigned char*[mapSize];
	for (int i = 0; i < mapSize; ++i) {
		tileMap[i] = new unsigned char[mapSize];
	}

	miniMap = new bool*[mapSize];
	for (int i = 0; i < mapSize; ++i) {
		miniMap[i] = new bool[mapSize];
	}

	for (int y = 0; y < mapSize; ++y) {
		for (int x = 0; x < mapSize; ++x) {
			tileMap[y][x] = _tileMap[y][x];
			miniMap[y][x] = false;
		}
	}
	spriteSheet = LoadTexture(spriteSheetName);
	if (strcmp(miniMapSheetName, "none") == 0) {
		miniMapSheet = 0;
	}
	else 
		miniMapSheet = LoadTexture(miniMapSheetName);
}

DungeonFloor::~DungeonFloor() {
	//cleanup arrays
	for (int i = 0; i < mapSize; ++i) {
		delete tileMap[i];
		delete miniMap[i];
	}
	delete tileMap;
	delete miniMap;
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

void DungeonFloor::eliminateEncountered() {
	std::ofstream ofs("outputmem.txt");
	for (Enemy &e : enemies) {
		ofs << e.getAI() << std::endl;
	}

	if (encountered != enemies.end()) {
		enemies.erase(encountered);
		encountered = enemies.end();
	}

	std::ofstream ofs2("outputmemafter.txt");
	for (Enemy &e : enemies) {
		ofs2 << e.getAI() << std::endl;
	}

	ofs.close();
	ofs2.close();
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
	player->update(program, time);
	//player-chest collision
	for (int i = 0; i < chests.size(); ++i) {
		while (player->collidesWith(chests[i])) {
			if (tries > maxTries) break;
			player->nudge(chests[i], 0.0f);
			++tries;
		}
	}
	//player-map collision
	mapCollision(*player, program);
	//chest-map collision
	for (int i = 0; i < chests.size(); ++i) {
		chests[i].update(program, time);
		mapCollision(chests[i], program);
	}
	//enemy collisions
	for (std::list<Enemy>::iterator i = enemies.begin(); i != enemies.end(); ++i) {
		//Enemy &enemy = enemies[i];
		i->update(program, time, this);
		//enemy-map collision
		mapCollision(*i, program);
		//enemy-player collision
		if (player->collidesWith(*i)) {
			/*if (tries > maxTries) break;
			player->nudge(enemy, 0.5f);
			++tries;*/
			encountered = i;
			//halt all movement before transition
			player->halt();
			for (std::list<Enemy>::iterator j = enemies.begin(); j != enemies.end(); ++j) {
				j->halt();
			}
		}
		//enemy-chest collision
		for (int j = 0; j < chests.size(); ++j) {
			while (i->collidesWith(chests[j])) {
				if (tries > maxTries) break;
				i->nudge(chests[j], 0.0f);
				++tries;
			}
		}
		//enemy-enemy collision
		for (std::list<Enemy>::iterator j = i; j != enemies.end(); ++j) {
			if (j == i) ++j;
			if (j == enemies.end()) break;
			while (i->collidesWith(*j)) {
				if (tries > maxTries) break;
				i->nudge(*j, 0.5f);
				++tries;
			}
		}
	}

	//minimap
	if (miniMapSheet != 0) {
		int radius = 3;
		int x, y;
		worldToTileCoordinates(player->position.x, player->position.y, x, y, mapSize);
		for (int i = x - radius; i <= x + radius; ++i) {
			for (int j = y - radius; j <= y + radius; ++j) {
				if (i >= 0 && j >= 0 && i < mapSize && j < mapSize && !miniMap[j][i]) miniMap[j][i] = true;
			}
		}
	}
}

void DungeonFloor::draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix) {

	//floor tiles
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
	//chests
	for (Chest &chest : chests)
		chest.draw(program, projectionMatrix, modelMatrix, viewMatrix);
	//enemies
	for (Enemy &enemy : enemies)
		enemy.draw(program, projectionMatrix, modelMatrix, viewMatrix);
	//player
	player->draw(program, projectionMatrix,	modelMatrix, viewMatrix);
	viewMatrix.identity();
	viewMatrix.Translate(-player->position.x, (-1.0f * player->position.y), 0);

	//minimap
	if (miniMapSheet != 0) {
		//tiles
		for (int y = 0; y < mapSize; ++y) {
			for (int x = 0; x < mapSize; ++x) {
				if ((!floorTile(x, y) || tileMap[y][x] == X || tileMap[y][x] == enter) && miniMap[y][x]) {
					modelMatrix.identity();
					modelMatrix.Translate(float(x)*0.05f*tileSize + player->position.x - 3.0f, (mapSize - float(y) - 1.0f)*0.05f*tileSize + player->position.y + 0.6f, 0.0f);
					program->setModelMatrix(modelMatrix);
					program->setProjectionMatrix(projectionMatrix);
					program->setViewMatrix(viewMatrix);
					DrawSpriteSheetSprite(program, tileMap[y][x], numx, numy, miniMapSheet, 0.05f*tileSize);
				}
			}
		}

		//chests
		int x, y;
		for (Chest &chest : chests) {
			worldToTileCoordinates(chest.position.x, chest.position.y, x, y, mapSize);
			if (miniMap[y][x]) {
				modelMatrix.identity();
				modelMatrix.Translate(0.05f*chest.position.x + player->position.x - 3.0f, 0.05f*chest.position.y + player->position.y + 0.6f, 0.0f);
				program->setModelMatrix(modelMatrix);
				program->setProjectionMatrix(projectionMatrix);
				program->setViewMatrix(viewMatrix);
				DrawSpriteSheetSprite(program, chestc, numx, numy, miniMapSheet, 0.05f*tileSize);
			}
		}

		//enemies
		for (Enemy &enemy : enemies) {
			worldToTileCoordinates(enemy.position.x, enemy.position.y, x, y, mapSize);
			if (miniMap[y][x]) {
				modelMatrix.identity();
				modelMatrix.Translate(0.05f*enemy.position.x + player->position.x - 3.0f, 0.05f*enemy.position.y + player->position.y + 0.6f, 0.0f);
				program->setModelMatrix(modelMatrix);
				program->setProjectionMatrix(projectionMatrix);
				program->setViewMatrix(viewMatrix);
				DrawSpriteSheetSprite(program, enemym, numx, numy, miniMapSheet, 0.05f*tileSize);
			}
		}

		//player
		modelMatrix.identity();
		modelMatrix.Translate(0.05f*player->position.x + player->position.x - 3.0f, 0.05f*player->position.y + player->position.y + 0.6f, 0.0f);
		program->setModelMatrix(modelMatrix);
		program->setProjectionMatrix(projectionMatrix);
		program->setViewMatrix(viewMatrix);
		DrawSpriteSheetSprite(program, playerm, numx, numy, miniMapSheet, 0.05f*tileSize);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void DungeonFloor::add(Enemy &e) {
	if (encountered == enemies.end()) {
		enemies.push_back(e);
		encountered = enemies.end();
	}
	else {
		enemies.push_back(e);
	}
}

void DungeonFloor::add(Chest &c) {
	chests.push_back(c);
}

void DungeonFloor::updateTiles(unsigned char **t) {
	for (int y = 0; y < mapSize; ++y) {
		for (int x = 0; x < mapSize; ++x) {
			tileMap[y][x] = t[y][x];
			miniMap[y][x] = false;
		}
	}
}

bool DungeonFloor::isEncountered() const { return encountered != enemies.end(); }
std::list<Enemy>::iterator DungeonFloor::getEncountered() const { return encountered; }
int DungeonFloor::getMapSize() const { return mapSize; }
float DungeonFloor::getTileSize() const { return tileSize; }
unsigned char** DungeonFloor::getTileMap() const { return tileMap; }
GLuint DungeonFloor::getSpriteSheet() const { return spriteSheet; }
std::vector<Chest>& DungeonFloor::getChests() { return chests; }
std::list<Enemy>& DungeonFloor::getEnemies() { return enemies; }

void DungeonFloor::setSpriteSheet(const char* name) { spriteSheet = LoadTexture(name); }