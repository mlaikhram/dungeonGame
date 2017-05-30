#include "Util.h"
#include "Entity.h"

Entity::Entity(const char *spriteSheetName, int index, int numx, int numy, Vector3 position, float size, Vector3 velocity, Vector3 acceleration, float rotation) :
	index(index), numx(numx), numy(numy), position(position), velocity(velocity), acceleration(acceleration), size(size), rotation(rotation),
	collidedTop(false), collidedBottom(false), collidedLeft(false), collidedRight(false), cliffLeft(false), cliffRight(false), cliffDown(false) {
	spriteSheet = LoadTexture(spriteSheetName);
}

void Entity::update(ShaderProgram *program, float time) {
	velocity.x = lerp(velocity.x, 0.0f, time * 7);
	velocity.y = lerp(velocity.y, 0.0f, time * 7);

	velocity.x += acceleration.x * time;
	velocity.y += acceleration.y * time;

	position.y += velocity.y * time;
	position.x += velocity.x * time;
}

void Entity::draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix) {
	modelMatrix.identity();
	//modelMatrix.Scale(0.5f, 0.5f, 1.0f);
	modelMatrix.Translate(position.x, position.y, position.z);
	//modelMatrix.Scale(size, size, 1.0f);
	program->setModelMatrix(modelMatrix);
	program->setProjectionMatrix(projectionMatrix);
	program->setViewMatrix(viewMatrix);
	DrawSpriteSheetSprite(program, index, numx, numy, spriteSheet, size);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

bool Entity::collidesWith(Entity &entity) {
	return (!(
		position.x - size / 2 > entity.position.x + entity.size / 2 ||
		position.x + size / 2 < entity.position.x - entity.size / 2 ||
		position.y - size / 2 > entity.position.y + entity.size / 2 ||
		position.y + size / 2 < entity.position.y - entity.size / 2));
}

void Entity::nudge(Entity &entity, float nudgePercent) {
	Vector3 responseVector = Vector3(position.x - entity.position.x, position.y - entity.position.y, 0.0f);
	responseVector.normalize2d();

	if (abs(responseVector.x) > abs(responseVector.y)) responseVector.y = 0;
	else responseVector.x = 0;

	position.x += responseVector.x * 0.008f * (1.0f - nudgePercent);
	position.y += responseVector.y * 0.008f * (1.0f - nudgePercent);

	entity.position.x -= responseVector.x * 0.008f * nudgePercent;
	entity.position.y -= responseVector.y * 0.008f * nudgePercent;
}