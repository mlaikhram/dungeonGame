#ifndef MKL_ENTITY
#define MKL_ENTITY

#include "Util.h"

class Entity {
public:
	Entity(const char *spriteSheetName, int index, int numx, int numy, Vector3 position, float size = 1.0f, Vector3 velocity = Vector3(0, 0, 0), Vector3 acceleration = Vector3(0, 0, 0), float rotation = 0.0f);
	virtual void update(ShaderProgram *program, float time);
	virtual void draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix);

	bool collidesWith(Entity &entity);
	void nudge(Entity &entity, float nudgePercent);
	void halt();

	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	float size;
	float rotation;
	bool collidedTop;
	bool collidedBottom;
	bool collidedLeft;
	bool collidedRight;
	bool cliffLeft;
	bool cliffRight;
	bool cliffDown;

protected:
	GLuint spriteSheet;
	int index;
	int numx;
	int numy;
	float lifetime;
};

#endif MKL_ENTITY