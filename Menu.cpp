#include "Menu.h"

Menu::Menu() : activeScreen(0) {}

void Menu::draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix) {
	menuScreens[activeScreen].draw(program, projectionMatrix, modelMatrix, viewMatrix);
}

int Menu::pollAndUpdate(ShaderProgram *program, float &elapsed, float &lastFrameTicks, float &ticks, float &fixedElapsed, SDL_Event &event) {

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