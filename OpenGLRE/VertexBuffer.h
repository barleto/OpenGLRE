#pragma once
#include <glad/glad.h>


/*
A Vertex Buffer Object (VBO) is a memory buffer in the high speed memory of your video card designed to hold information about vertices. 
VBOs can also store information such as normals, texcoords, indicies, etc.
*/
class VertexBuffer
{
private:
	GLuint mId;
public:
	VertexBuffer(const GLvoid* data, unsigned int size);
	~VertexBuffer();
	void bind() const;
	void unbind() const;
};

