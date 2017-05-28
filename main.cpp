#include <ctime>
#include "TierList.h"
#include "Util.h"
#include "DungeonFloor.h"
#include "DungeonFloorGenerator.h"
#include "Entity.h"
#include "MenuOption.h"

#ifdef _WINDOWS
#define RESOURCE_FOLDER ""
#else
#define RESOURCE_FOLDER "dungeonGame.app/Contents/Resources/"
#endif


SDL_Window* displayWindow;

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	//displayWindow = SDL_CreateWindow("MAGNETIC MAN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 360, SDL_WINDOW_OPENGL);
	displayWindow = SDL_CreateWindow("Dungeon Thing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	//SDL_SetWindowFullscreen(displayWindow, SDL_WINDOW_FULLSCREEN);
	SDL_GL_MakeCurrent(displayWindow, context);
#ifdef _WINDOWS
	glewInit();
#endif

	//glViewport(0, 0, 640, 360);
	glViewport(0, 0, 1280, 720);
	ShaderProgram program(RESOURCE_FOLDER"vertex_textured.glsl", RESOURCE_FOLDER"fragment_textured.glsl");

	Matrix projectionMatrix;
	Matrix modelMatrix;
	Matrix viewMatrix;

	projectionMatrix.setOrthoProjection(-3.55f, 3.55f, -2.0f, 2.0f, -1.0f, 1.0f);
	glUseProgram(program.programID);

	//GLuint spriteSheet = LoadTexture("tilemap_dungeon1.png");

	float elapsed = 0.0f;
	float lastFrameTicks = 0.0f;
	float ticks = 0.0f;
	float fixedElapsed = 0.0f;

	float accel = 10.0f;

	//generate pseudorandom seed
	time_t time;
	std::time(&time);
	unsigned int seed = unsigned int(time);
	srand(seed);
	//output file for debugging
	std::ofstream ofs("output.txt");

	Entity player("tiles.png", 52, 20, 20, Vector3(0.0f, 0.0f, 0.0f), 0.75 * TILE_SIZE);
	//DungeonFloor *floor = new DungeonFloor(100, TILE_SIZE, levelData, "tilemap_dungeon1.png", 10, 10, &player);
	DungeonFloorGenerator dfg(25, 5, TILE_SIZE, &player);
	DungeonFloor *floor = dfg.generate("tilemap_dungeon1.png", 10, 10);

	MenuOption menu("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG.", Vector3(0, 0, 0), "letters.png", 16, 16, 0.2f);


	SDL_Event event;
	bool done = false;
	while (!done) {

		// input //////////////////////////////////////////////////////////////////////////////////////////////////
		player.acceleration.x = 0.0f;
		player.acceleration.y = 0.0f;
		const Uint8 *keys = SDL_GetKeyboardState(NULL);
		if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_K]) {
			player.acceleration.x -= accel;
		}
		if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_SEMICOLON]) {
			player.acceleration.x += accel;
		}
		if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_O]) {
			player.acceleration.y += accel;
		}
		if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_L]) {
			player.acceleration.y -= accel;
		}
		if (keys[SDL_SCANCODE_SPACE] && floor->exitCollision(&program)) {
			delete floor;
			floor = dfg.generate("tilemap_dungeon1.png", 10, 10);
		}
		// TESTING KEYBIND ONLY //
		if (keys[SDL_SCANCODE_R]) {
			delete floor;
			floor = dfg.generate("tilemap_dungeon1.png", 10, 10);
		}
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				done = true;
			}
		}

		// update /////////////////////////////////////////////////////////////////////////////////////////////////

		//timestep
		ticks = (float)SDL_GetTicks() / 1000.0f;
		elapsed = ticks - lastFrameTicks;
		lastFrameTicks = ticks;

		// 60 FPS (1.0f/60.0f)
		fixedElapsed = elapsed;
		if (fixedElapsed > FIXED_TIMESTEP * MAX_TIMESTEPS) {
			fixedElapsed = FIXED_TIMESTEP * MAX_TIMESTEPS;
		}
		while (fixedElapsed >= FIXED_TIMESTEP) {
			fixedElapsed -= FIXED_TIMESTEP;
			player.update(&program, FIXED_TIMESTEP);
			floor->mapCollision(player, &program);
		}
		player.update(&program, fixedElapsed);
		floor->mapCollision(player, &program);

		// draw ///////////////////////////////////////////////////////////////////////////////////////////////////
		glClear(GL_COLOR_BUFFER_BIT);

		floor->draw(&program, projectionMatrix, modelMatrix, viewMatrix);
		menu.draw(&program, projectionMatrix, modelMatrix, viewMatrix);
		player.draw(&program, projectionMatrix, modelMatrix, viewMatrix);
		viewMatrix.identity();
		viewMatrix.Translate(-player.position.x, (-1.0f * (player.position.y + TILE_SIZE)), 0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		SDL_GL_SwapWindow(displayWindow);
	}
	SDL_Quit();
	/*time_t time;
	std::time(&time);
	unsigned int seed = unsigned int(time);
	srand(seed);

	std::ofstream ofs("output.txt");

	std::vector<std::vector<std::string>> money(5);
	money[0].push_back("stone");
	money[0].push_back("dirt");
	money[1].push_back("copper");
	money[1].push_back("tin");
	money[2].push_back("bronze");
	money[3].push_back("silver");
	money[4].push_back("gold");
	money[4].push_back("platinum");

	TierList<std::string> tl(money, 0);


	tl.display(ofs);
	for (int i = 0; i < 5; ++i) {
		ofs << "tier " << i << std::endl;
		std::vector<std::string> spawns = tl.spawnObjects(20);
		for (std::string spawn : spawns)
			ofs << spawn << std::endl;

		ofs << std::endl;
		++tl;
	}
	*/
	ofs.close();
	return 0;
}
