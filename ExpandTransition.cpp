#include "ExpandTransition.h"

ExpandTransition::ExpandTransition(Entity *player, Entity expander, float growthRate, float maxSize) : Transition(player), expander(expander), growthRate(growthRate), maxSize(maxSize) {}

void ExpandTransition::recenter() {
	expander.position = player->position;
}

bool ExpandTransition::fullGrow() { return expander.size >= maxSize; }
bool ExpandTransition::fullShrink() { return expander.size <= 0.0f; }

void ExpandTransition::growStep(float &fixedElapsed) { expander.size += growthRate * fixedElapsed; }
void ExpandTransition::shrinkStep(float &fixedElapsed) { expander.size -= growthRate * fixedElapsed; }

void ExpandTransition::draw(ShaderProgram *program, Matrix &projectionMatrix, Matrix &modelMatrix, Matrix &viewMatrix) {
	expander.draw(program, projectionMatrix, modelMatrix, viewMatrix);
}
