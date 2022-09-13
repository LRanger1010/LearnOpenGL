#include "pch.h"
#include "Skybox.h"
#include "VertexBufferLayout.h"

static const float vertices[] = {
	//right
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,

	//left
	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,

	//top
	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,

	//bottom
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,

	//front
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,

	//back
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
};

static const unsigned int MaxQuadCount = 6;
static const unsigned int MaxVertexCount = 4 * MaxQuadCount;
static const unsigned int MaxIndexCount = 6 * MaxQuadCount;

static const std::vector<std::string> paths = {
	"res/textures/skybox/right.jpg",
	"res/textures/skybox/left.jpg",
	"res/textures/skybox/top.jpg",
	"res/textures/skybox/bottom.jpg",
	"res/textures/skybox/front.jpg",
	"res/textures/skybox/back.jpg"
};

#define DEFAULT_CUBEMAP_SHADER "Skybox"

Skybox::Skybox()
{
	m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
	{
		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 3);
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
	m_Shader = std::make_unique<Shader>(DEFAULT_CUBEMAP_SHADER);
	m_CubeMap = std::make_unique<CubeMap>(paths);
	BindTexture(0);
}

Skybox::~Skybox()
{

}

void Skybox::Update()
{
	m_Shader->Bind();
	glm::mat4 view = glm::mat4(glm::mat3(MATRIX_VIEW));
	m_MVP = MATRIX_PROJ * view;
	m_Shader->SetUniformMat4f("u_MVP", m_MVP);
}

void Skybox::Draw()
{
	GLCALL(glDepthFunc(GL_LEQUAL));
	m_Renderer.Draw(m_VAO, *m_IBO, *m_Shader);
	GLCALL(glDepthFunc(GL_LESS));
}

void Skybox::BindTexture(unsigned int slot /*= 0*/)
{
	m_Shader->Bind();
	m_CubeMap->Bind(slot);
	m_Shader->SetUniform1i("u_CubeMap", slot);
}
