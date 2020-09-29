#pragma once

class VertexElementBuffer
{
	unsigned int vboId_;
	unsigned int eboId_;

	float* vertices{};
	unsigned int* indices{};
public:
	VertexElementBuffer();
	~VertexElementBuffer();
	void bind() const;
	void unbind() const;
	bool isBound() const;
	unsigned int getVertexBufferId() const;
	unsigned int getElementBufferId() const;
	void setVertices(float vertices[], unsigned int count);
	void setIndices(unsigned int indices[], unsigned int count);
};
