#pragma once
#include "Renderer.h"
#include "Shader.h"
#include "CubeMap.h"

class Skybox
{
public:
	Skybox();
	~Skybox();

	void Update();
	void Draw();

private:
	Renderer m_Renderer;
	VertexArray m_VAO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_IBO;
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<CubeMap> m_CubeMap;
};