#include "MainMenu.h"

MainMenu::MainMenu() : Menu() {
	//mainScreen
	MenuOption play("Play", Vector3(), "letters.png", 16, 16, 0.2f, 0.5f);
	MenuOption settings("Settings", Vector3(0.0f, -0.4f, 0.0f), "letters.png", 16, 16, 0.2f, 0.5f);
	MenuOption controls("Controls", Vector3(0.0f, -0.8f, 0.0f), "letters.png", 16, 16, 0.2f, 0.5f);
	MenuOption credits("Credits", Vector3(0.0f, -1.2f, 0.0f), "letters.png", 16, 16, 0.2f, 0.5f);
	MenuOption exit("Exit", Vector3(0.0f, -1.6f, 0.0f), "letters.png", 16, 16, 0.2f, 0.5f);
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

int MainMenu::update(ShaderProgram *program, float time, float mousex, float mousey, int mousedOption) {

	// if they clicked on a menuOption, determine which option they clicked on
	switch (activeScreen) {
	case 0: // mainScreen
		switch (mousedOption) {
		case 0: // play
			return STATE_LEVELSELECT;
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

	menuScreens[activeScreen].update(program, time, mousex, mousey);
	return STATE_MAINMENU;

}