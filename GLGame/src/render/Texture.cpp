#include "Texture.h"

#include <glad/glad.h>


#include "../fileio/stb_image.h"
#include "../Debug.h"

Texture::Texture(const std::string& path)
{
	data_ = stbi_load(path.c_str(), &width_, &height_, &channels_, 0);
	glGenTextures(1, &id_);
}

Texture::~Texture()
{
	stbi_image_free(data_);
}

int Texture::getWidth() const
{
	return width_;
}

int Texture::getHeight() const
{
	return height_;
}

int Texture::getChannels() const
{
	return channels_;
}

unsigned char* Texture::getTexture() const
{
	return data_;
}

void Texture::load() const
{
	glBindTexture(GL_TEXTURE, id_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, data_);
	glGenerateMipmap(id_);
	
}
