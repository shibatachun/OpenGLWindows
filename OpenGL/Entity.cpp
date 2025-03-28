#include "Entity.h"

Entity::Entity(Shader shader, unsigned int ID) :ID(ID), shader(shader)
{
}

void Entity::Draw()
{
	this->shader.use();
	glBindVertexArray(this->ID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
