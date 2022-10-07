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
}

Quad::~Quad()
{

}

void Quad::Update()
{
	
}

void Quad::Draw(Shader& shader)
{
	m_Renderer.Draw(m_VAO, *m_IBO, shader);
}
