#include "Shader.h"
#include "Renderer.h"

const std::string shaderDir = "res/shaders/";
const std::string shaderExt = ".shader";

Shader::Shader(const std::string& shaderName)
{
	ShaderSource ss = m_FindShader(shaderName);
	m_RenderID = m_CreateShader(ss.vertexShaderSource, ss.fragmentShaderSource);
}

Shader::~Shader()
{
	GLCALL(glDeleteProgram(m_RenderID));
}

void Shader::Bind() const
{
	GLCALL(glUseProgram(m_RenderID));
}

void Shader::Unbind() const
{
	GLCALL(glUseProgram(0));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	int location = m_GetUniformLocation(name);
	GLCALL(glUniform3f(location, v0, v1, v2));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	int location = m_GetUniformLocation(name);
	GLCALL(glUniform4f(location, v0, v1, v2, v3));
}

unsigned int Shader::m_CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	GLCALL(unsigned int program = glCreateProgram());
	unsigned int vs = m_CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fs = m_CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	GLCALL(glAttachShader(program, vs));
	GLCALL(glAttachShader(program, fs));
	GLCALL(glLinkProgram(program));
	GLCALL(glValidateProgram(program));

	GLCALL(glDeleteShader(vs));
	GLCALL(glDeleteShader(fs));

	return program;
}

ShaderSource Shader::m_ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);
	std::string line;
	std::stringstream ss[2];
	enum class ShaderType {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1,
	};
	ShaderType type = ShaderType::NONE;
	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	return{ ss[0].str(), ss[1].str() };
}

unsigned int Shader::m_CompileShader(unsigned int type, const std::string& source)
{
	GLCALL(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCALL(glShaderSource(id, 1, &src, NULL));
	GLCALL(glCompileShader(id));

	int result;
	GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCALL(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "Shader!" << std::endl;
		std::cout << message << std::endl;
	}

	return id;
}

ShaderSource Shader::m_FindShader(const std::string& shaderName)
{
	std::string filepath = shaderDir + shaderName + shaderExt;
	return m_ParseShader(filepath);
}

int Shader::m_GetUniformLocation(const std::string& name)
{
	if (m_uniformLocationMap.find(name) != m_uniformLocationMap.end())
		return m_uniformLocationMap[name];

	GLCALL(int location = glGetUniformLocation(m_RenderID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

	m_uniformLocationMap[name] = location;
	return location;
}
