#include "VertexElementBuffer.h"

#include <glad/glad.h>

VertexElementBuffer::VertexElementBuffer() : vboId_(0), eboId_(0)
{
	glGenBuffers(1, &vboId_);
	glGenBuffers(1, &eboId_);
}

void VertexElementBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboId_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId_);
}

void VertexElementBuffer::unbind() const
{
	if (isBound())
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

bool VertexElementBuffer::isBound() const
{
	int boundvbo;
	int boundebo;
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &boundvbo);
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &boundebo);
	
	return static_cast<unsigned>(boundvbo) == vboId_ && static_cast<unsigned>(boundebo) == eboId_; 
}

unsigned int VertexElementBuffer::getVertexBufferId() const
{
	return vboId_;
}

unsigned int VertexElementBuffer::getElementBufferId() const
{
	return eboId_;
}

void VertexElementBuffer::setVertices(const float vertices[], unsigned int count)
{
	
}

void VertexElementBuffer::setIndices(int indices[])
{
}
