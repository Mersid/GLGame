#pragma once
#include <string>

class Texture
{
	int width;
	int height;
	int channels;
	unsigned char* data;
public:
	Texture(const std::string& path);
	
};
