#include "Util.h"
#include "Entity.h"

Entity::Entity(const char *spriteSheetName, int index, int numx, int numy, Vector3 position, float size, bool isStatic, Vector3 velocity, Vector3 acceleration, float rotation) :
	index(index), numx(numx), numy(numy), isStatic(isStatic), position(position), velocity(velocity), acceleration(acceleration), size(size), rotation(rotation), exists(true),
	collidedTop(false), collidedBottom(false), collidedLeft(false), collidedRight(false), cliffLeft(false), cliffRight(false), cliffDown(false) {
	spriteSheet = LoadTexture(spriteSheetName);
}

void Entity::update(ShaderProgram *program, float time) {
	velocity.x = lerp(velocity.x, 0.0f, time * 5);
	velocity.y = lerp(velocity.y, 0.0f, time * 5);

	velocity.x += acceleration.x * time;
	velocity.y += acceleration.y * time;

	position.y += velocity.y * time;
	position.x += velocity.x * time;
}

void Entity::draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix) {
	modelMatrix.identity();
	modelMatrix.Translate(position.x, position.y, position.z);
	program->setModelMatrix(modelMatrix);
	program->setProjectionMatrix(projectionMatrix);
	program->setViewMatrix(viewMatrix);
	DrawSpriteSheetSprite(program, index, numx, numy, spriteSheet, size);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}