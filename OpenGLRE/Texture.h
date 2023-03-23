#pragma once
#include <glad/glad.h>
#include <string>

enum class TextureWrapMode
{
	REPEAT, MIRROR_REPEAT, CLAMP_EDGE, CLAMP_BORDER
};

class Texture2D
{
public:
	Texture2D(const std::string& filePath);
	~Texture2D();
	int getHeight() const { return mHeight; };
	int getWidth() const { return mWidth; };
	int getNrChannels() const { return mNrChannels; };
	void bind() const;
	void unbind() const;
	void setTextureWrapMode(TextureWrapMode textureWrapMode);
	void activate(unsigned int unit);
private:
	int mWidth, mHeight, mNrChannels;
	TextureWrapMode mTextureWrapMode;
	GLuint mId;
};