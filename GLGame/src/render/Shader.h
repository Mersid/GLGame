#pragma once
#include <string>


#include "glm/detail/type_mat.hpp"
#include "glm/detail/type_vec.hpp"


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
	void setVec2(const std::string& name, glm::vec2& vector) const;
	void setVec3(const std::string& name, glm::vec3& vector) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setVec4(const std::string& name, glm::vec4& vector) const;
	void setVec4(const std::string& name, float x, float y, float z, float w) const;
	void setMat2(const std::string& name, glm::mat2& matrix) const;
	void setMat3(const std::string& name, glm::mat3& matrix) const;
	void setMat4(const std::string& name, glm::mat4& matrix) const;

private:
	unsigned int compileShader(const std::string& shaderSrc, unsigned int shaderType);
	unsigned int compileProgram(unsigned int vertexShaderId, unsigned int fragmentShaderId) const;
	
};

