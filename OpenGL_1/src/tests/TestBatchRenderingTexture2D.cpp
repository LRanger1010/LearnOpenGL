#include "pch.h"
#include "TestBatchRenderingTexture2D.h"
#include "VertexBufferLayout.h"

namespace test {

	static const float vertices[] = {
		//position	  //texture coord	//index
		-1.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,	//0
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,	//1
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,		//2
		-1.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,	//3

		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	//4
		1.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,	//5
		1.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,		//6
		0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,	//7
	};

	static const unsigned int indice[] = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4
	};

	static const int samplers[] = { 0,1 };

	TestBatchRenderingTexture2D::TestBatchRenderingTexture2D()
	{
		m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
		{
			VertexBufferLayout layout;
			layout.Push(GL_FLOAT, 3);
			layout.Push(GL_FLOAT, 2);
			layout.Push(GL_FLOAT, 1);
			m_VAO.AddBuffer(*m_VBO, layout);
		}
		m_IBO = std::make_unique<IndexBuffer>(indice, 12);
		m_Shader = std::make_unique<Shader>("batchTexture");

		m_Proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

		m_Shader->Bind();
		m_Tex1 = std::make_unique<Image>("res/textures/cherno.jpg");
		m_Tex2 = std::make_unique<Image>("res/textures/sky.jpg");
		m_Tex1->Bind(0);
		m_Tex2->Bind(1);
		m_Shader->SetUniform1iv("u_Textures", 2, samplers);
		m_Shader->SetUniformMat4f("u_MVP", m_Proj);
		
	}

	TestBatchRenderingTexture2D::~TestBatchRenderingTexture2D()
	{

	}

	void TestBatchRenderingTexture2D::OnUpdate(float deltaTime)
	{

	}

	void TestBatchRenderingTexture2D::OnRender()
	{
		m_Renderer.Draw(m_VAO, *m_IBO, *m_Shader);
	}

	void TestBatchRenderingTexture2D::OnGUI()
	{

	}

}