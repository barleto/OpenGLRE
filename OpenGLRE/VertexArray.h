#pragma once
#include <glad/glad.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"


/*
A Vertex Array Object (VAO) is an object which contains one or more Vertex Buffer Objects 
and is designed to store the information for a complete rendered object. 
*/
class VertexArray
{
private:
	GLuint mId;
public:
	VertexArray();
	~VertexArray();
	void addBuffer(const VertexBuffer& vb, const IndexBuffer& ib, const VertexBufferLayout& layout);
	void bind() const;
	void unbind() const;
};

