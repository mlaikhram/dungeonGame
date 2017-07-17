#include <ctime>
#include "TierList.h"
#include "Util.h"
#include "DungeonFloor.h"
#include "DungeonFloorGenerator.h"
#include "Dungeon.h"
#include "Entity.h"
#include "Text.h"
#include "MenuOption.h"
#include "MenuScreen.h"
#include "MainMenu.h"
#include "LevelSelectMenu.h"
#include "WanderAI.h"

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
	//SDL_ShowCursor(SDL_DISABLE);
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

	//float accel = 10.0f;

	//generate pseudorandom seed
	time_t time;
	std::time(&time);
	unsigned int seed = unsigned int(time);
	srand(seed);
	//output file for debugging
	std::ofstream ofs("output.txt");

	Entity player("tiles.png", 52, 20, 20, Vector3(), 0.75 * TILE_SIZE);
	std::vector<std::vector<Enemy>> bosses(1);
	for (int i = 0; i < 10; ++i) {
		MoveAI *staticAI = new WanderAI(0.0f);
		bosses[0].push_back(Enemy("tiles.png", i + 112, 20, 20, staticAI, &player, Vector3(), 3.0f * TILE_SIZE));
	}

	Dungeon dungeon(1, 1, 1, &(bosses.at(0)), &player);

	//Entity cursor("tiles.png", 52, 20, 20, Vector3(), 0.05f * TILE_SIZE);
	Text t("hello", Vector3(0.0f, 1.6f, 0.0f), "letters.png", 16, 16, 0.2f, CENTERED);

	MainMenu mainMenu;
	LevelSelectMenu levelSelectMenu;
	//float m_x = 0.0f;
	//float m_y = 0.0f;
	int gameState = STATE_MAINMENU;

	SDL_Event event;
	bool done = false;
	const Uint8 *keys;
	while (!done) {

		keys = SDL_GetKeyboardState(NULL);

		switch (gameState) {
		case STATE_MAINMENU:

			gameState = mainMenu.pollAndUpdate(&program, elapsed, lastFrameTicks, ticks, fixedElapsed, event);
			// draw
			glClear(GL_COLOR_BUFFER_BIT);
			mainMenu.draw(&program, projectionMatrix, modelMatrix, viewMatrix);
			//cursor.draw(&program, projectionMatrix, modelMatrix, viewMatrix);
			t.draw(&program, projectionMatrix, modelMatrix, viewMatrix);
			//viewMatrix.identity();
			//viewMatrix.Translate(-player.position.x, (-1.0f * player.position.y), 0);
			break;

		case STATE_LEVELSELECT:
			
			gameState = levelSelectMenu.pollAndUpdate(&program, elapsed, lastFrameTicks, ticks, fixedElapsed, event);
			// draw
			glClear(GL_COLOR_BUFFER_BIT);
			levelSelectMenu.draw(&program, projectionMatrix, modelMatrix, viewMatrix);
			//cursor.draw(&program, projectionMatrix, modelMatrix, viewMatrix);
			//t.draw(&program, projectionMatrix, modelMatrix, viewMatrix);
			//viewMatrix.identity();
			//viewMatrix.Translate(-player.position.x, (-1.0f * player.position.y), 0);
			break;

		case STATE_DUNGEON:

			gameState = dungeon.pollAndUpdate(&program, elapsed, lastFrameTicks, ticks, fixedElapsed, event, keys);
			// draw
			glClear(GL_COLOR_BUFFER_BIT);
			dungeon.draw(&program, projectionMatrix, modelMatrix, viewMatrix);
			//player.draw(&program, projectionMatrix, modelMatrix, viewMatrix);
			//viewMatrix.identity();
			//viewMatrix.Translate(-player.position.x, (-1.0f * player.position.y), 0);

			//glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			break;

		case STATE_ENCOUNTER:

			break;

		default:
			done = true;
			break;
		}

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
