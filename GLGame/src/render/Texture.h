﻿#pragma once
#include <string>

class Texture
{
	unsigned int id_{};
	
	int width_{};
	int height_{};
	int channels_{};
	unsigned char* data_;
public:
	Texture(const std::string& path);
	~Texture();
	int getWidth() const;
	int getHeight() const;
	int getChannels() const;
	unsigned int getId() const;
	unsigned char* getTexture() const;
	void load() const;
};
