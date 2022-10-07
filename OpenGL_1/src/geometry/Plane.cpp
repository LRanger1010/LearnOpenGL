#include "pch.h"
#include "Plane.h"
#include "VertexBufferLayout.h"

static const unsigned int MaxIndexCount = 6;

static const float vertices[] = {
	// positions            // normals         // texcoords
		-2.0f, -0.5f,  2.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
		2.0f, -0.5f,  2.0f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
		2.0f, -0.5f, -2.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
	   -2.0f, -0.5f, -2.0f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
};

#define DEFAULT_PLANE_TEXTURE_PATH "res/textures/wood.png"

Plane::Plane()
{
	m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
	{
		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 3);
		layout.Push(GL_FLOAT, 3);
		layout.Push(GL_FLOAT, 2);
		m_VAO.AddBuffer(*m_VBO, layout);
	}

	unsigned int indice[MaxIndexCount];
	unsigned int offset = 0;
	for (int i = 0; i < MaxIndexCount; i += 6)
	{
		indice[i] = offset;
		indice[i + 1] = offset + 1;
		indice[i + 2] = offset + 2;
		indice[i + 3] = offset + 2;
		indice[i + 4] = offset + 3;
		indice[i + 5] = offset;

		offset += 4;
	}

	m_IBO = std::make_unique<IndexBuffer>(indice, MaxIndexCount);
	m_Tex = std::make_unique<Image>(DEFAULT_PLANE_TEXTURE_PATH);
}

Plane::~Plane()
{
}

void Plane::Update()
{
}

void Plane::Draw(Shader& shader)
{
	m_Renderer.Draw(m_VAO, *m_IBO, shader);
}

void Plane::BindImage(unsigned int slot /*= 0*/)
{
	m_Tex->Bind(slot);
}
