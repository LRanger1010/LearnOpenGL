#pragma once
#include "Renderer.h"

class Quad
{
public:
	Quad();
	~Quad();

	void Update();
	void Draw();
	void BindTexture(unsigned int textureId, unsigned int slot = 0);
	void ResetShader(const std::string& name);

private:
	Renderer m_Renderer;
	VertexArray m_VAO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_IBO;
	std::unique_ptr<Shader> m_Shader;
	glm::mat4 m_MVP;
};