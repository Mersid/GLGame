#include "VertexElementBuffer.h"


#include <memory>
#include <glad/glad.h>
#include "../Debug.h"

VertexElementBuffer::VertexElementBuffer() : vboId_(0), eboId_(0)
{
	glGenBuffers(1, &vboId_);
	glGenBuffers(1, &eboId_);
}

VertexElementBuffer::~VertexElementBuffer()
{
	delete[] vertices;
	delete[] indices;

	// Might want to call glDeleteBuffers too...
}

void VertexElementBuffer::bind() const
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

void VertexElementBuffer::setVertices(float vertices[], unsigned int count)
{
	if (!isBound())
		Log("You must bind the vertex array buffer before setting the vertices");
	
	delete[] this->vertices;
	this->vertices = new float[count];

	for (unsigned int i = 0; i < count; i++)
		this->vertices[i] = vertices[i];

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, this->vertices, GL_STATIC_DRAW);	
}

void VertexElementBuffer::setIndices(unsigned int indices[], unsigned int count)
{
	if (!isBound())
		Log("You must bind the element array buffer before setting the vertices");
	
	delete[] this->indices;
	this->indices = new unsigned int[count];

	for (unsigned int i = 0; i < count; i++)
		this->indices[i] = indices[i];

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, this->indices, GL_STATIC_DRAW);
}
