#pragma once
#include "pch.h"

struct ShaderSource
{
	std::string vertexShaderSource;
	std::string fragmentShaderSource;
};

class Shader
{
public:
	Shader(const std::string& shaderName);
	~Shader();

	void Bind() const;
	void Unbind() const;
	void SetUniform1i(const std::string& name, int v);
	void SetUniform1iv(const std::string& name, unsigned int count, const int* value);
	void SetUniform1f(const std::string& name, float v);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform3fv(const std::string& name, glm::vec3 vec);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, glm::mat4 mat);

private:
	unsigned int m_RenderID;
	mutable std::unordered_map<std::string, int> m_uniformLocationMap;

	unsigned int m_CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
	ShaderSource m_ParseShader(const std::string& filepath);
	unsigned int m_CompileShader(unsigned int type, const std::string& source);
	ShaderSource m_FindShader(const std::string& shaderName);
	int m_GetUniformLocation(const std::string& name) const;
};