#pragma once
#include <glad/glad.h>


/*
An IndexBufferObject (IBO or EBO) holds information about the elements index array of a specific VBO.
*/
class IndexBuffer
{
private:
	GLuint mId;
	GLuint mCount;
public:
	IndexBuffer(const GLvoid* data, unsigned int size);
	~IndexBuffer();
	void bind() const;
	void unbind() const;
	inline GLuint getCount() const { return mCount; };
};

