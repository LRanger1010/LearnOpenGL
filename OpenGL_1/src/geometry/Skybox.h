#pragma once
#include "Renderer.h"
#include "Shader.h"
#include "CubeMap.h"
#include "camera/Camera.h"

class Skybox
{
public:
	Skybox();
	~Skybox();

	void Update();
	void Draw();
	void BindTexture(unsigned int slot = 0);

private:
	Renderer m_Renderer;
	VertexArray m_VAO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_IBO;
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<CubeMap> m_CubeMap;
	glm::mat4 m_MVP;
};