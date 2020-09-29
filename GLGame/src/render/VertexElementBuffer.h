#pragma once

class VertexElementBuffer
{
	unsigned int vboId_;
	unsigned int eboId_;
public:
	VertexElementBuffer();
	void bind();
	void unbind() const;
	bool isBound() const;
	unsigned int getVertexBufferId() const;
	unsigned int getElementBufferId() const;
	void setVertices(const float vertices[], unsigned int count);
	void setIndices(int indices[]);
};
