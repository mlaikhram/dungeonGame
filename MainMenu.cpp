#include "MainMenu.h"

MainMenu::MainMenu() {
	//mainScreen
	MenuOption play("play", Vector3(), "letters.png", 16, 16, 0.2f, 0.5f);
	MenuOption settings("settings", Vector3(), "letters.png", 16, 16, 0.2f, 0.5f);
	MenuOption controls("controls", Vector3(), "letters.png", 16, 16, 0.2f, 0.5f);
	MenuOption credits("credits", Vector3(), "letters.png", 16, 16, 0.2f, 0.5f);
	MenuOption exit("exit", Vector3(), "letters.png", 16, 16, 0.2f, 0.5f);
	std::vector<MenuOption> vec1;
	vec1.push_back(play);
	vec1.push_back(settings);
	vec1.push_back(controls);
	vec1.push_back(credits);
	vec1.push_back(exit);
	MenuScreen mainScreen(vec1);

	//settingScreen
	MenuOption back("back", Vector3(), "letters.png", 16, 16, 0.2f, 0.5f);
	std::vector<MenuOption> vec2;
	vec2.push_back(back);
	MenuScreen settingScreen(vec2);

	//controlsScreen
	std::vector<MenuOption> vec3;
	vec3.push_back(back);
	MenuScreen controlsScreen(vec3);

	//creditsScreen
	std::vector<MenuOption> vec4;
	vec4.push_back(back);
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

int MainMenu::update(ShaderProgram *program, float time, float mousex, float mousey) {
	return -1;
}