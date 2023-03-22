#pragma once
#include <glad/glad.h>
#include <string>
#include <sstream>

struct ShaderProgramSource {
	std::string vertex;
	std::string fragment;
};

class ShaderProgram
{
private:
	GLuint mId;
	std::string mFilePath;
	unsigned int getUniformLocation(const std::string& name);
	GLuint compileShader(GLenum type, const std::string& source);
	ShaderProgramSource parseShader(const std::string& filepath);
public:
	ShaderProgram(const std::string& filepath);
	~ShaderProgram();
	void bind() const;
	void unbind() const;

	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
};

