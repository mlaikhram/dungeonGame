#include "LevelSelectMenu.h"

LevelSelectMenu::LevelSelectMenu() : Menu() {
	//dungeonSelectScreen
	std::vector<MenuOption> vec1;
	MenuOption back("back", Vector3(0, -2.0f + 1.1f  * TILE_SIZE, 0), "letters.png", 16, 16, 0.2f, 0.5f);
	vec1.push_back(back);
	for (int i = 0; i < 1; ++i) {
		vec1.push_back(MenuOption("dungeon1", Vector3(), "letters.png", 16, 16, 0.2f, 0.5f));
	}
	MenuScreen dungeonSelectScreen(vec1);

	//floorSelectScreen
	std::vector<MenuOption> vec2;
	//MenuOption back("back", Vector3(), "letters.png", 16, 16, 0.2f, 0.5f);
	vec2.push_back(back);
	for (int i = 0; i < 10; ++i) {
		// 1.9f is the starting point for the MenuOptions
		vec2.push_back(MenuOption("f" + std::to_string(i * 10 + 1), Vector3(0, 1.9f - i * TILE_SIZE, 0), "letters.png", 16, 16, 0.2f, 0.5f));
	}
	MenuScreen floorSelectScreen(vec2);

	//difficultySelectSscreen
	std::vector<MenuOption> vec3;
	//MenuOption back("back", Vector3(), "letters.png", 16, 16, 0.2f, 0.5f);
	MenuOption normal("normal", Vector3(), "letters.png", 16, 16, 0.2f, 0.5f);
	vec3.push_back(back);
	std::vector<std::string> difficulties = {"normal", "hard", "expert"};
	for (int i = 0; i < 3; ++i) {
		// 1.9f is the starting point for the MenuOptions
		vec3.push_back(MenuOption(difficulties[i], Vector3(0, 1.9f - i * TILE_SIZE, 0), "letters.png", 16, 16, 0.2f, 0.5f));
	}

	MenuScreen difficultySelectScreen(vec3);

	// Adding screen1,screen2 to menuScreens
	menuScreens.push_back(dungeonSelectScreen);
	menuScreens.push_back(floorSelectScreen);
	menuScreens.push_back(difficultySelectScreen);
}

int LevelSelectMenu::update(ShaderProgram *program, float time, float mousex, float mousey, int mousedOption) {
	menuScreens[activeScreen].update(program, time, mousex, mousey);

	// if they clicked on a menuOption, determine which option they clicked on
	switch (activeScreen) {
	case 0: // dungeonSelectScreen
		switch (mousedOption) {
		case -1: // anytime the user hovers but doesn't click
			break;
		case 0: // back
			return STATE_MAINMENU;
			break;
		default: // if they choose an option, store it and move to next screen
			dungeonSelected = mousedOption;
			activeScreen = 1;
			break;
		}
		break;
	case 1: // floorSelectScreen
		switch (mousedOption) {
		case -1:
			break;
		case 0:
			activeScreen = 0;
			break;
		default:
			floorSelected = mousedOption;
			activeScreen = 2;
			break;
		}
		break;
	case 2: // difficultySelectScreen
		switch (mousedOption) {
		case -1:
			break;
		case 0:
			activeScreen = 1;
			break;
		default:
			difficultySelected = mousedOption;
			return STATE_DUNGEON;
			break;
		}
		break;
	default:
		break;
	}
	return STATE_LEVELSELECT;

}