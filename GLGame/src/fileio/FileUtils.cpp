#include "FileUtils.h"
#include <iostream>
#include <fstream>

std::string FileUtils::readFile(const std::string& path)
{
	std::ifstream stream;
	stream.exceptions(std::ifstream::failbit);

	try
	{
		stream.open(path);
		std::stringstream stringStream;
		stringStream << stream.rdbuf();
		stream.close();
		return stringStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Failed to read file: " << path << ". Error: " << e.code() << "\n" << e.what() << std::endl;
		return "";
	}
}
