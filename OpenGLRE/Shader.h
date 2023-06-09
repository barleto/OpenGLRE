#pragma once
#include <glad/glad.h>
#include <string>
#include <sstream>
#include <unordered_map>
#include <glm/glm.hpp>


struct ShaderProgramSource {
	std::string vertex;
	std::string fragment;
};

class Shader
{
private:
	GLuint mId;
	std::string mFilePath;
	unsigned int getUniformLocation(const std::string& name);
	GLuint compileShader(GLenum type, const std::string& source);
	ShaderProgramSource parseShader(const std::string& filepath);
	std::unordered_map<std::string, GLuint> mUniforLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();
	void bind() const;
	void unbind() const;

	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniform1i(const std::string& name, int i);
	void setUniform1f(const std::string& name, float i);
	void setUniformMatrix4fv(const std::string& name, glm::mat4& mat);
};

