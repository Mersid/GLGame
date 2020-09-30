#include "Shader.h"

#include <string>


#include "../Debug.h"


Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	unsigned int vertexShaderId = compileShader(FileUtils::readFile(vertexPath), GL_VERTEX_SHADER);
	unsigned int fragmentShaderId = compileShader(FileUtils::readFile(fragmentPath), GL_FRAGMENT_SHADER);

	id = compileProgram(vertexShaderId, fragmentShaderId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
	
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::use() const
{
	glUseProgram(id);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

unsigned int Shader::compileShader(const std::string& shaderSrc, unsigned int shaderType)
{
	const char* shaderSrcP = shaderSrc.c_str();
	const unsigned int id = glCreateShader(shaderType);
	glShaderSource(id, 1, &shaderSrcP, nullptr);
	glCompileShader(id);

	// Check for errors
	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		char* log = new char[length];
		glGetShaderInfoLog(id, length, nullptr, log);
		Log(std::string("Shader failed to compile:\n") + std::string(log));
		delete[] log;
		return 0;
	}
	
	return id;
}

unsigned int Shader::compileProgram(unsigned int vertexShaderId, unsigned int fragmentShaderId) const
{
	const unsigned int programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	glLinkProgram(programId);

	// Check for errors
	int success;
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		int length;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &length);

		char* log = new char[length];
		glGetProgramInfoLog(id, length, nullptr, log);
		Log(std::string("Shader program failed to compile:\n") + std::string(log));
		delete[] log;
		return 0;
	}
	
	return programId;
}

