#include "VertexArray.h"

VertexArray::VertexArray()
{
	unsigned int VAO;
	glGenVertexArrays(1, &mId);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &mId);
}

void VertexArray::addBuffer(const VertexBuffer& vb, const IndexBuffer& ib, const VertexBufferLayout& layout)
{
	this->bind();
	vb.bind();
	ib.bind();
	const auto& elements = layout.getElelements();
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized? GL_TRUE : GL_FALSE, layout.getStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::bind() const
{
	glBindVertexArray(mId);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
