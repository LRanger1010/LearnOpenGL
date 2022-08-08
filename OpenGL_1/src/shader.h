#pragma once
#include<iostream>
#include <string>
#include<fstream>
#include<sstream>
#include <unordered_map>
#include "glm/glm.hpp"

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
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, glm::mat4 mat);

private:
	unsigned int m_RenderID;
	std::unordered_map<std::string, int> m_uniformLocationMap;

	unsigned int m_CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
	ShaderSource m_ParseShader(const std::string& filepath);
	unsigned int m_CompileShader(unsigned int type, const std::string& source);
	ShaderSource m_FindShader(const std::string& shaderName);
	int m_GetUniformLocation(const std::string& name);
};