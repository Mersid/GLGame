#include "Texture.h"

#include "../fileio/stb_image.h"
#include "../Debug.h"

Texture::Texture(const std::string& path)
{
	data_ = stbi_load(path.c_str(), &width_, &height_, &channels_, 0);
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
