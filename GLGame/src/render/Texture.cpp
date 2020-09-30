#include "Texture.h"


#include <string>
#include <glad/glad.h>


#include "../fileio/stb_image.h"
#include "../Debug.h"

Texture::Texture(const std::string& path)
{
	stbi_set_flip_vertically_on_load(true);
	data_ = stbi_load(path.c_str(), &width_, &height_, &channels_, 0);
	if (!data_)
	{
		Log(std::string("Image ") + std::string(path + std::string(" failed to load")));
	}
	
	glGenTextures(1, &id_);
}

Texture::~Texture()
{
	stbi_image_free(data_);
	glDeleteTextures(1, &id_);
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

unsigned Texture::getId() const
{
	return id_;
}

unsigned char* Texture::getTexture() const
{
	return data_;
}

void Texture::load() const
{
	glBindTexture(GL_TEXTURE_2D, id_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (channels_ == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, data_);
	else if (channels_ == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data_);
	else
		Log("Image has unusual number of channels");
	
	glGenerateMipmap(GL_TEXTURE_2D);
}


