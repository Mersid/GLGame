#pragma once
#include <string>


class Shader
{
public:
	unsigned int id;

	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void use() const;

	// Sets uniform
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

private:
	unsigned int compileShader(const std::string& shaderSrc, unsigned int shaderType);
	unsigned int compileProgram(unsigned int vertexShaderId, unsigned int fragmentShaderId) const;
	
};

