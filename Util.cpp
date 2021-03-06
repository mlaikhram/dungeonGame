//#ifdef _WINDOWS
//#include <GL/glew.h>
//#endif

#include "Util.h"
#include "DungeonFloor.h"
#include "Text.h"

bool TextIntComp::operator() (const Text &lhs, const Text &rhs) const
{
	return atoi(lhs.text.c_str()) < atoi(rhs.text.c_str());
}

GLuint LoadTexture(const char *image_path)
{
	SDL_Surface *surface = IMG_Load(image_path);
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface(surface);
	return textureID;
}

void DrawSpriteSheetSprite(ShaderProgram *program, int index, int spriteCountX, int spriteCountY, GLuint textureID, float tileSize) {

	float u = (float)(((int)index) % spriteCountX) / (float)spriteCountX;
	float v = (float)(((int)index) / spriteCountX) / (float)spriteCountY;
	float spriteWidth = 1.0f / (float)spriteCountX;
	float spriteHeight = 1.0f / (float)spriteCountY;

	GLfloat texCoords[] = {
		u, v + spriteHeight,
		u + spriteWidth, v,
		u, v,
		u + spriteWidth, v,
		u, v + spriteHeight,
		u + spriteWidth, v + spriteHeight
	};

	float vertices[] = { -0.5f*tileSize, -0.5f*tileSize, 0.5f*tileSize, 0.5f*tileSize, -0.5f*tileSize, 0.5f*tileSize, 0.5f*tileSize, 0.5f*tileSize, -0.5f*tileSize, -0.5f*tileSize, 0.5f*tileSize, -0.5f*tileSize };

	glBindTexture(GL_TEXTURE_2D, textureID);
	glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
	glEnableVertexAttribArray(program->positionAttribute);

	glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
	glEnableVertexAttribArray(program->texCoordAttribute);

	/*float colors[] = {
		1.0f, 0.0f, 0.0f, 0.5f,
		1.0f, 0.0f, 0.0f, 0.5f,
		1.0f, 0.0f, 0.0f, 0.5f,
		1.0f, 0.0f, 0.0f, 0.5f,
		1.0f, 0.0f, 0.0f, 0.5f,
		1.0f, 0.0f, 0.0f, 0.5f
	};

	glVertexAttribPointer(program->vertexShader, 2, GL_FLOAT, false, 0, colors);
	glEnableVertexAttribArray(program->vertexShader);*/

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(program->positionAttribute);
	glDisableVertexAttribArray(program->texCoordAttribute);
	//glDisableVertexAttribArray(program->vertexShader);


}

float lerp(float v0, float v1, float t) {
	return (1.0f - t)*v0 + t*v1;
}

void worldToTileCoordinates(float worldX, float worldY, int &gridX, int &gridY, int mapSize) {
	gridX = (int)(worldX / TILE_SIZE);
	//gridY = (int)(-(worldY) / TILE_SIZE);
	gridY = (int)(-((worldY / TILE_SIZE) - (mapSize - 1)));
}

void tileToWorldCoordinates(int gridX, int gridY, float &worldX, float &worldY, int mapSize) {
	worldX = (float)(gridX * TILE_SIZE);
	worldY = (float)((-gridY + mapSize - 1) * TILE_SIZE);
}

float distance(Vector3 a, Vector3 b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

std::vector<std::string> parseText(std::string &text) {
	std::vector<std::string> ans = std::vector<std::string>();
	int begin = 0;
	int end = 1;
	while (end < text.size()) {
		if (text[end] == '.') {
			ans.push_back(text.substr(begin, end - begin));
			begin = end + 1;
			++end;
		}
		++end;
	}
	ans.push_back(text.substr(begin));
	return ans;
}

std::string padZeroes(int num, int maxDigits) {
	std::string ans = std::to_string(num);

	while (ans.length() < maxDigits) {
		ans = "0" + ans;
	}
	return ans;
}