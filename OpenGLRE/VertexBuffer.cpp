#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const GLvoid* data, unsigned int size)
{
	GLuint VBO;
	glGenBuffers(1, &VBO);
	this->mId = VBO;
	glBindBuffer(GL_ARRAY_BUFFER, this->mId);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &(this->mId));
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, this->mId);
}

void VertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
