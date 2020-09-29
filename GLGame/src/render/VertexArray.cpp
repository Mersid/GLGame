#include "VertexArray.h"

#include <glad/glad.h>

VertexArray::VertexArray() : id_(0) // ctor init 0 to suppress warnings
{
	glGenVertexArrays(1, &id_);
}

void VertexArray::bind() const
{
	glBindVertexArray(id_);
}

void VertexArray::unbind() const
{
	if (isBound())
		glBindVertexArray(0);
}

bool VertexArray::isBound() const
{
	int boundvao;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &boundvao);

	return boundvao == id_;
}

unsigned VertexArray::getId() const
{
	return id_;
}
