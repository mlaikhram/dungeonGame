#include "MainMenu.h"

MainMenu::MainMenu() : activeScreen(0) {
	//mainScreen
	MenuOption play("play", Vector3(), "letters.png", 16, 16, 0.2f, 0.5f);
	MenuOption settings("settings", Vector3(0.0f, -0.4f, 0.0f), "letters.png", 16, 16, 0.2f, 0.5f);
	MenuOption controls("controls", Vector3(0.0f, -0.8f, 0.0f), "letters.png", 16, 16, 0.2f, 0.5f);
	MenuOption credits("credits", Vector3(0.0f, -1.2f, 0.0f), "letters.png", 16, 16, 0.2f, 0.5f);
	MenuOption exit("exit", Vector3(0.0f, -1.6f, 0.0f), "letters.png", 16, 16, 0.2f, 0.5f);
	std::vector<MenuOption> vec1;
	vec1.push_back(play);
	vec1.push_back(settings);
	vec1.push_back(controls);
	vec1.push_back(credits);
	vec1.push_back(exit);
	MenuScreen mainScreen(vec1);

	//settingScreen
	MenuOption setting("setting", Vector3(), "letters.png", 16, 16, 0.2f, 0.5f);
	std::vector<MenuOption> vec2;
	vec2.push_back(setting);
	MenuScreen settingScreen(vec2);

	//controlsScreen
	MenuOption control("controls", Vector3(), "letters.png", 16, 16, 0.2f, 0.5f);
	std::vector<MenuOption> vec3;
	vec3.push_back(controls);
	MenuScreen controlsScreen(vec3);

	//creditsScreen
	MenuOption credit("credits", Vector3(), "letters.png", 16, 16, 0.2f, 0.5f);
	std::vector<MenuOption> vec4;
	vec4.push_back(credits);
	MenuScreen creditsScreen(vec4);

	// Adding screen1,screen2 to menuScreens
	menuScreens.push_back(mainScreen);
	menuScreens.push_back(settingScreen);
	menuScreens.push_back(controlsScreen);
	menuScreens.push_back(creditsScreen);
}

void MainMenu::draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix) {
	menuScreens[activeScreen].draw(program, projectionMatrix, modelMatrix, viewMatrix);
}

int MainMenu::update(ShaderProgram *program, float time, float mousex, float mousey, int mousedOption) {
	menuScreens[activeScreen].update(program, time, mousex, mousey);

	// if they clicked on a menuOption, determine which option they clicked on
	switch (activeScreen) {
	case 0: // mainScreen
		switch (mousedOption) {
		case 0: // play
			return STATE_DUNGEON;
			break;
		case 1: // switch to settingScreen
			activeScreen = 1;
			break;
		case 2: // switch to controlsScreen
			activeScreen = 2;
			break;
		case 3: // switch to creditsScreen
			activeScreen = 3;
			break;
		case 4: // close game
			return STATE_END;
			break;
		default:
			break;
		}
		break;
	case 1: // settingScreen
		switch (mousedOption) {
		case 0:
			activeScreen = 0;
			break;
		default:
			break;
		}
		break;
	case 2: // controlsScreen
		switch (mousedOption) {
		case 0:
			activeScreen = 0;
			break;
		default:
			break;
		}
		break;
	case 3: // creditsScreen
		switch (mousedOption) {
		case 0:
			activeScreen = 0;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return STATE_MAINMENU;

}

int MainMenu::pollAndUpdate(ShaderProgram *program, float &elapsed, float &lastFrameTicks, float &ticks, float &fixedElapsed, SDL_Event &event) {

	int mousedOption = -1;
	float m_x = (((float)event.motion.x / 1280) * 7.1f) - 3.55f;
	float m_y = (((float)(720 - event.motion.y) / 720) * 4.0f) - 2.0f;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
			return STATE_END;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			mousedOption = menuScreens[activeScreen].mousedOption(m_x, m_y);
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
	/*while (fixedElapsed >= FIXED_TIMESTEP) {
		fixedElapsed -= FIXED_TIMESTEP;
		update(program, FIXED_TIMESTEP, m_x, m_y, mousedOption);
		//cursor.position.x = m_x;
		//cursor.position.y = m_y;
	}*/
	return update(program, fixedElapsed, m_x, m_y, mousedOption);
	//cursor.position.x = m_x;
	//cursor.position.y = m_y;
}