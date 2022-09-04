#include "pch.h"
#include "TestDynamicBatching.h"
#include "Vertex.h"

namespace test {

	const static unsigned int MaxQuadCount = 1000;
	const static unsigned int MaxVertexCount = MaxQuadCount * 4;
	const static unsigned int MaxIndexCount = MaxQuadCount * 6;

	/*static const unsigned int indice[] = {
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4
	};*/

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

	static Vertex* CreateQuad(Vertex* target, float x, float y, float texId)
	{
		float size = 1.0f;
		*target = Vertex(glm::vec3( x, y, 0.0f ), glm::vec2( 0.0f, 0.0f ), texId);
		target++;
		*target = Vertex(glm::vec3(x + size, y, 0.0f ), glm::vec2( 1.0f, 0.0f ), texId);
		target++;
		*target = Vertex(glm::vec3(x + size, y + size, 0.0f ), glm::vec2(1.0f, 1.0f ), texId);
		target++;
		*target = Vertex(glm::vec3(x, y + size, 0.0f ), glm::vec2(0.0f, 1.0f ), texId);
		target++;

		return target;
	}

	TestDynamicBatching::TestDynamicBatching()
	{
		m_VBO = std::make_unique<VertexBuffer>(MaxVertexCount * sizeof(Vertex));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoord));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexIndex));

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
		m_Shader = std::make_unique<Shader>("batchTexture");

		m_Proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

		m_Tex1 = std::make_unique<Image>("res/textures/cherno.jpg");
		m_Tex2 = std::make_unique<Image>("res/textures/sky.jpg");
	}

	TestDynamicBatching::~TestDynamicBatching()
	{

	}

	void TestDynamicBatching::OnUpdate(float deltaTime)
	{
		if (m_x > 2.0f)
			m_x = -2.0f;
		m_x += deltaTime * 0.01f;

		if (m_y > 1.5f)
			m_y = -1.5f;
		m_y += deltaTime * 0.01f;

		const unsigned int vertexCount = 1000;
		Vertex vertices[vertexCount];
		Vertex* buffer = vertices;
		for (float y = -1.5f; y < 1.5f; y ++)
		{
			for (float x = -2.0f; x < 2.0f; x++)
			{
				buffer = CreateQuad(buffer, x, y, 0.0f);
			}
		}
		buffer = CreateQuad(buffer, m_x, m_y, 0.0f);

		m_VBO->Bind(vertices, sizeof(vertices));
	}

	void TestDynamicBatching::OnRender()
	{
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