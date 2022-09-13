#include "pch.h"
#include "Cube.h"
#include "VertexBufferLayout.h"
#include "camera/Camera.h"

static const unsigned int MaxQuadCount = 6;
static const unsigned int MaxVertexCount = 4 * MaxQuadCount;
static const unsigned int MaxIndexCount = 6 * MaxQuadCount;

static const float vertices[] = {
	//position			//texture coord
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,	//0
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f,	//1
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f,	//2
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,	//3

	0.5f, -0.5f, 0.0f, 0.0f, 0.0f,	//4
	0.5f, -0.5f, -1.0f, 1.0f, 0.0f,	//5
	0.5f, 0.5f, -1.0f, 1.0f, 1.0f,	//6
	0.5f, 0.5f, 0.0f, 0.0f, 1.0f,	//7

	-0.5f, -0.5f, -1.0f, 0.0f, 0.0f,	//8
	0.5f, -0.5f, -1.0f, 1.0f, 0.0f,	//9
	0.5f, 0.5f, -1.0f, 1.0f, 1.0f,	//10
	-0.5f, 0.5f, -1.0f, 0.0f, 1.0f,	//11

	-0.5f, -0.5f, -1.0f, 0.0f, 0.0f,	//12
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f,	//13
	-0.5f, 0.5f, 0.0f, 1.0f, 1.0f,	//14
	-0.5f, 0.5f, -1.0f, 0.0f, 1.0f,	//15

	-0.5f, 0.5f, 0.0f, 0.0f, 0.0f,	//16
	0.5f, 0.5f, 0.0f, 1.0f, 0.0f,	//17
	0.5f, 0.5f, -1.0f, 1.0f, 1.0f,	//18
	-0.5f, 0.5f, -1.0f, 0.0f, 1.0f,	//19

	-0.5f, -0.5f, -1.0f, 0.0f, 0.0f,	//20
	0.5f, -0.5f, -1.0f, 1.0f, 0.0f,	//21
	0.5f, -0.5f, 0.0f, 1.0f, 1.0f,	//22
	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,	//23
};
#define DEFAULT_CUBE_SHADER "texture"
#define DEFAULT_CUBE_TEXTURE_PATH "res/textures/container2.png"

Cube::Cube()
{
	m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
	{
		VertexBufferLayout layout;
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
	m_Shader = std::make_unique<Shader>(DEFAULT_CUBE_SHADER);

	m_Tex = std::make_unique<Image>(DEFAULT_CUBE_TEXTURE_PATH);
	BindTexture(0);
}

Cube::~Cube()
{
}

void Cube::Update()
{
	m_Shader->Bind();
	glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	// ע�⣬���ǽ�����������Ҫ�����ƶ������ķ������ƶ���
	/*glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);*/

	m_MVP = MATRIX_VP * model;
	m_Shader->SetUniformMat4f("u_MVP", m_MVP);
}

void Cube::Draw()
{
	m_Renderer.Draw(m_VAO, *m_IBO, *m_Shader);
}

void Cube::BindTexture(unsigned int slot /*= 0*/)
{
	m_Shader->Bind();
	m_Tex->Bind(slot);
	m_Shader->SetUniform1i("u_Texture", slot);
}