#include "Texture.h"
#include "stb_image.h"
#include <iostream>
#include <cassert>

static GLenum GetGlEnum(TextureWrapMode textureWrapMode)
{
	switch (textureWrapMode)
	{
	case TextureWrapMode::REPEAT:
		return GL_REPEAT;
	case TextureWrapMode::MIRROR_REPEAT:
		return GL_MIRRORED_REPEAT;
	case TextureWrapMode::CLAMP_EDGE:
		return GL_CLAMP_TO_EDGE;
	case TextureWrapMode::CLAMP_BORDER:
		return GL_CLAMP_TO_BORDER;
	default:
		assert(false);
	}
}

Texture2D::Texture2D(const std::string& filePath)
	: mTextureWrapMode(TextureWrapMode::REPEAT)
{
	glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	auto textWrap = GetGlEnum(mTextureWrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load and generate the texture
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filePath.c_str(), &mWidth, &mHeight, &mNrChannels, 0);
	if (data)
	{
		if (mNrChannels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		} else if (mNrChannels == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &mId);
}

void Texture2D::bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, mId);
}

void Texture2D::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::setTextureWrapMode(TextureWrapMode textureWrapMode)
{
	mTextureWrapMode = textureWrapMode;
	glBindTexture(GL_TEXTURE_2D, mId);
	auto textWrap = GetGlEnum(mTextureWrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textWrap);
}
