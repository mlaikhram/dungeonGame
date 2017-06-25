#include "Dungeon.h"
#include "Util.h"

Dungeon::Dungeon(int id, int floorCounter, int difficulty, Entity *player) : id(id), floorCounter(floorCounter), difficulty(difficulty), dfg(50, 5, TILE_SIZE, player), player(player) {
	std::string sheet = "tilemap_dungeon" + std::to_string(id) + ".png";
	currentFloor = dfg.generate(sheet.c_str(), "tilemap_minimap.png", 10, 10);
}

void Dungeon::nextFloor() {
	std::string sheet = "tilemap_dungeon" + std::to_string(id) + ".png";
	delete currentFloor;
	currentFloor = dfg.generate(sheet.c_str(), "tilemap_minimap.png", 10, 10);
	++floorCounter;
}

int Dungeon::update(ShaderProgram *program, float time) {
	currentFloor->update(program, time);
	return STATE_DUNGEON;
}

int Dungeon::pollAndUpdate(ShaderProgram *program, float &elapsed, float &lastFrameTicks, float &ticks, float &fixedElapsed, SDL_Event &event, const Uint8 *keys) {
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

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
			return STATE_END;
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
			if (currentFloor->tileCollision(program, X)) {
				nextFloor();
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
}

void Dungeon::draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix) {
	currentFloor->draw(program, projectionMatrix, modelMatrix, viewMatrix);
}
