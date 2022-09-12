#include "pch.h"
#include "Quad.h"
#include "VertexBufferLayout.h"

static const float vertices[] = {
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,	//0
	1.0f, -1.0f, 0.0f, 1.0f, 0.0f,	//1
	1.0f, 1.0f, 0.0f, 1.0f, 1.0f,	//2
	-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,	//3
};

unsigned int indice[] = {
	0, 1, 2,
	2, 3, 0,
};
#define DEFAULT_QUAD_SHADER "screen"

Quad::Quad()
{
	m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
	{
		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 3);
		layout.Push(GL_FLOAT, 2);
		m_VAO.AddBuffer(*m_VBO, layout);
	}
	m_IBO = std::make_unique<IndexBuffer>(indice, 6);
	m_Shader = std::make_unique<Shader>(DEFAULT_QUAD_SHADER);
}

Quad::~Quad()
{

}

void Quad::Update()
{
	
}

void Quad::Draw()
{
	m_Renderer.Draw(m_VAO, *m_IBO, *m_Shader);
}

void Quad::BindTexture(unsigned int textureId, unsigned int slot)
{
	m_Shader->Bind();
	GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
	GLCALL(glBindTexture(GL_TEXTURE_2D, textureId));
	m_Shader->SetUniform1i("u_Texture", slot);
}

void Quad::ResetShader(const std::string& name)
{
	m_Shader = nullptr;
	m_Shader = std::make_unique<Shader>(name);
}
