#include "TestDynamicBatching.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Vertex.h"
#include <array>

namespace test {

	const static unsigned int MaxQuadCount = 1000;
	const static unsigned int MaxVertexCount = MaxQuadCount * 4;
	const static unsigned int MaxIndexCount = MaxQuadCount * 6;

	static const unsigned int indice[] = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4
	};

	//static const float vertices[] = {
	//	//position	  //texture coord	//index
	//	-1.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,	//0
	//	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,	//1
	//	-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,		//2
	//	-1.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,	//3

	//	0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	//4
	//	1.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,	//5
	//	1.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,		//6
	//	0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,	//7
	//};

	static const int samplers[] = { 0,1 };

	static std::array<Vertex, 4> CreateQuad(float x, float y, float texId)
	{
		float size = 1.0f;
		Vertex v0(glm::vec3( x, y, 0.0f ), glm::vec2( 0.0f, 0.0f ), texId);
		Vertex v1(glm::vec3(x + size, y, 0.0f ), glm::vec2( 1.0f, 0.0f ), texId);
		Vertex v2(glm::vec3(x + size, y + size, 0.0f ), glm::vec2(1.0f, 1.0f ), texId);
		Vertex v3(glm::vec3(x, y + size, 0.0f ), glm::vec2(0.0f, 1.0f ), texId);
		return{ v0, v1, v2, v3 };
	}

	TestDynamicBatching::TestDynamicBatching()
	{
		m_VBO = std::make_unique<VertexBuffer>(MaxVertexCount * sizeof(Vertex));
		m_VAO.Bind();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoord));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexIndex));

		m_IBO = std::make_unique<IndexBuffer>(indice, 12);
		m_Shader = std::make_unique<Shader>("batchTexture");

		m_Proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

		m_Tex1 = std::make_unique<Texture>("res/textures/cherno.jpg");
		m_Tex2 = std::make_unique<Texture>("res/textures/sky.jpg");
	}

	TestDynamicBatching::~TestDynamicBatching()
	{

	}

	void TestDynamicBatching::OnUpdate(float deltaTime)
	{
		if (m_x > 2.0f)
			m_x = -2.0f;
		m_x += deltaTime;
		auto q0 = CreateQuad(m_x, -0.5f, 0.0f);
		auto q1 = CreateQuad(0.5f, -0.5f, 1.0f);
		Vertex vertices[8];
		memcpy(vertices, q0.data(), q0.size() * sizeof(Vertex));
		memcpy(vertices + q0.size(), q1.data(), q1.size() * sizeof(Vertex));
		m_VBO->Bind(vertices, sizeof(vertices));
	}

	void TestDynamicBatching::OnRender()
	{
		m_Renderer.Clear();
		m_Shader->Bind();
		m_Tex1->Bind(0);
		m_Tex2->Bind(1);
		m_Shader->SetUniform1iv("u_Textures", 2, samplers);
		m_Shader->SetUniformMat4f("u_MVP", m_Proj);
		m_Renderer.Draw(m_VAO, *m_IBO, *m_Shader);
	}

	void TestDynamicBatching::OnGUI()
	{

	}
}