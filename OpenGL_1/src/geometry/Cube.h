#pragma once
#include "Renderer.h"
#include "Image.h"

class Cube
{
public:
	Cube();
	~Cube();

	void Update();
	void Draw();
	void BindTexture(unsigned int slot = 0);

private:
	Renderer m_Renderer;
	VertexArray m_VAO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_IBO;
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<Image> m_Tex;
	glm::mat4 m_MVP;
};