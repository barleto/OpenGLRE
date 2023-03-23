#include "Shader.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <cassert>

ShaderProgramSource Shader::parseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            if (type == ShaderType::NONE) continue;

            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str()};
}

GLuint Shader::compileShader(GLenum type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(id);
        assert(false);
    }

    return id;
}

Shader::Shader(const std::string& filepath) 
    : mFilePath(filepath), mId(0)
{

    auto shaderSource = parseShader(filepath);
    auto vertexShader = compileShader(GL_VERTEX_SHADER, shaderSource.vertex);
    auto fragmentShader = compileShader(GL_FRAGMENT_SHADER, shaderSource.fragment);
    
    int success;
    char infoLog[512];

    // link shaders
    mId = glCreateProgram();
    glAttachShader(mId, vertexShader);
    glAttachShader(mId, fragmentShader);
    glLinkProgram(mId);
    // check for linking errors
    glGetProgramiv(mId, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(mId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        glDeleteProgram(mId);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(mId);
}

void Shader::bind() const
{
    glUseProgram(mId);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

unsigned int Shader::getUniformLocation(const std::string& name)
{
    if (mUniforLocationCache.find(name) != mUniforLocationCache.end()) 
    {
        return mUniforLocationCache[name];
    }

    auto location = glGetUniformLocation(mId, name.c_str());
    if (location == -1)
    {
        std::cout << "WARNING::SHADER::PROGRAM::UNIFORM_NAME_DOESNT_EXIST : " << name << std::endl;

    }
    return location;
}


void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform1i(const std::string& name, int i)
{
    glUniform1i(getUniformLocation(name), i);
}

void Shader::SetUniform1f(const std::string& name, float f)
{
    glUniform1f(getUniformLocation(name), f);
}
