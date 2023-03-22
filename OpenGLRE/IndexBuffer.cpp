#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const GLvoid* data, unsigned int count)
	: mCount(count)
{
	GLuint VBO;
	glGenBuffers(1, &VBO);
	this->mId = VBO;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &(this->mId));
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mId);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , 0);
}
