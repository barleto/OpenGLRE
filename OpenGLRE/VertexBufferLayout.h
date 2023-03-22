#pragma once
#include <vector>
#include <glad/glad.h>
#include <cassert>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	bool normalized;

	static unsigned int GetSizeOfType(GLenum type) {
		switch (type)
		{
		case GL_FLOAT:
			return sizeof(GLfloat);
		case GL_UNSIGNED_INT:
			return sizeof(GLuint);
		case GL_UNSIGNED_BYTE:
			return sizeof(GLubyte);
		default:
			assert(false);
			return 0;
			break;
		}
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> mElements;
	unsigned int mStride;
public:
	VertexBufferLayout(unsigned int stride) : mStride(0){};

	void push(GLenum type, unsigned int count, bool normalized)
	{
		mStride += count * VertexBufferElement::GetSizeOfType(type);
		mElements.push_back({ type, count, normalized });
	};

	inline std::vector<VertexBufferElement> getElelements() const { return mElements; };
	inline unsigned int getStride() const { return mStride; };
};

