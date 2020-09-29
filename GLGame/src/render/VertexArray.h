#pragma once

class VertexArray
{
	unsigned int id_;
	
public:
	VertexArray();
	void bind() const;
	void unbind() const;
	bool isBound() const;
	unsigned int getId() const;
};
