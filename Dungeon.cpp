#include "Dungeon.h"
#include "Util.h"

Dungeon::Dungeon(int id, int floorCounter, int difficulty, Entity *player) : id(id), floorCounter(floorCounter), difficulty(difficulty), dfg(50, 5, TILE_SIZE, player), player(player),
transition("tiles.png", 52, 20, 20, Vector3(), 0.0f), transitionPhase(-1), bossFloor(false), 
floorCountHUD("FLOOR" + std::to_string(floorCounter), Vector3(player->position.x - 3.0f, player->position.y + 1.9f, 0.0f), "letters.png", 16, 16, 0.2f * TILE_SIZE, LEFT_JUST) {
	std::string sheet = "tilemap_dungeon" + std::to_string(id) + ".png";
	currentFloor = dfg.generate(sheet.c_str(), "tilemap_minimap.png", 10, 10);
}

void Dungeon::nextFloor() {
	std::string sheet = "tilemap_dungeon" + std::to_string(id) + ".png";
	delete currentFloor;
	if (floorCounter % 10 == 0) {
		bossFloor = !bossFloor;
	}
	if (bossFloor) {
		currentFloor = generateBossFloor(floorCounter / 10 - 1, sheet);
		floorCountHUD.setText("BOSS " + std::to_string((int)(floorCounter / 10)));
	}
	else {
		currentFloor = dfg.generate(sheet.c_str(), "tilemap_minimap.png", 10, 10);
		//++floorCounter;
		floorCountHUD.setText("FLOOR" + std::to_string(++floorCounter));
	}
}

DungeonFloor* Dungeon::generateBossFloor(int index, std::string spriteSheetName) {
	int mapSize = 13;
	unsigned char **tileMap = new unsigned char*[mapSize];
	for (int i = 0; i < mapSize; ++i) {
		tileMap[i] = new unsigned char[mapSize];
	}
	//init corners
	tileMap[0][0] = SEFNW;
	tileMap[0][mapSize - 1] = SWFNE;
	tileMap[mapSize - 1][0] = NEFSW;
	tileMap[mapSize - 1][mapSize - 1] = NWFSE;

	//init top and bottom rows
	for (int x = 1; x < mapSize - 1; ++x) {
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

	//init entrance
	tileMap[mapSize - 2][mapSize / 2] = enter;
	tileToWorldCoordinates(mapSize / 2, mapSize - 2, player->position.x, player->position.y, mapSize);

	//init exit
	tileMap[mapSize / 2][mapSize / 2] = X;
	//spawn boss on exit

	DungeonFloor *floor = new DungeonFloor(mapSize, TILE_SIZE, tileMap, spriteSheetName.c_str(), "tilemap_minimap.png", 10, 10, player); //need an empty spritesheet to not generate minimap or keyword none
	return floor;
}

int Dungeon::update(ShaderProgram *program, float time) {
	currentFloor->update(program, time);
	floorCountHUD.position.x = player->position.x - 3.0f;
	floorCountHUD.position.y = player->position.y + 1.9f;
	return STATE_DUNGEON;
}

int Dungeon::pollAndUpdate(ShaderProgram *program, float &elapsed, float &lastFrameTicks, float &ticks, float &fixedElapsed, SDL_Event &event, const Uint8 *keys) {
	switch (transitionPhase) {
	case 0:
		transition.size += (0.1f * 7.1f);
		if (transition.size >= 7.1f) transitionPhase = 1;
		break;
	case 1:
		nextFloor();

		transition.position.x = player->position.x;
		transition.position.y = player->position.y;
		transitionPhase = 2;
		break;
	case 2:
		transition.size -= (0.1f * 7.1f);
		if (transition.size <= 0.0f) {
			transition.size = 0.0f;
			transitionPhase = -1;
		}
		break;
	default:
		float accel = 10.0f;
		player->acceleration.x = 0.0f;
		player->acceleration.y = 0.0f;
		keys = SDL_GetKeyboardState(NULL);
		if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_K]) {
			player->acceleration.x -= accel;
		}
		if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_SEMICOLON]) {
			player->acceleration.x += accel;
		}
		if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_O]) {
			player->acceleration.y += accel;
		}
		if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_L]) {
			player->acceleration.y -= accel;
		}
		//temp for testing
		bool cheat = false;
		if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_C]) {
			cheat = true;
		}

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				return STATE_END;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
				if (currentFloor->tileCollision(program, X) || cheat) {
					//nextFloor();
					transition.position.x = player->position.x;
					transition.position.y = player->position.y;
					transitionPhase = 0;
					break;
				}
				for (Chest& chest : currentFloor->getChests()) {
					int gridX, gridY;
					worldToTileCoordinates(chest.position.x, chest.position.y, gridX, gridY, currentFloor->getMapSize());
					if (currentFloor->tileCollision(program, gridX, gridY)) {
						chest.startOpen(*player);
					}
				}
			}
		}
		//timestep
		ticks = (float)SDL_GetTicks() / 1000.0f;
		elapsed = ticks - lastFrameTicks;
		lastFrameTicks = ticks;

		fixedElapsed = elapsed;
		if (fixedElapsed > FIXED_TIMESTEP * MAX_TIMESTEPS) {
			fixedElapsed = FIXED_TIMESTEP * MAX_TIMESTEPS;
		}
		while (fixedElapsed >= FIXED_TIMESTEP) {
			fixedElapsed -= FIXED_TIMESTEP;
			update(program, FIXED_TIMESTEP);
		}
		update(program, fixedElapsed);
		break;
	}
	return STATE_DUNGEON;
}

void Dungeon::draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix) {
	currentFloor->draw(program, projectionMatrix, modelMatrix, viewMatrix);
	floorCountHUD.draw(program, projectionMatrix, modelMatrix, viewMatrix);
	transition.draw(program, projectionMatrix, modelMatrix, viewMatrix);
}
