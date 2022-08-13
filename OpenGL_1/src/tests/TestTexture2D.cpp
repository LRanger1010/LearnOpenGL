#include "TestTexture2D.h"
#include "VertexBufferLayout.h"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

	static const std::string resPath = "res/textures/";

	static const float vertices[] = {
		//position	  //texture coord
		-0.5f, -0.5f, 0.0f, 0.0f,	//0
		0.5f, -0.5f, 1.0f, 0.0f,	//1
		0.5f, 0.5f, 1.0f, 1.0f,		//2
		-0.5f, 0.5f, 0.0f, 1.0f,	//3
	};

	static const unsigned int indice[] = {
		0, 1, 2,
		2, 3, 0
	};

	TestTexture2D::TestTexture2D()
		:m_Translation(0.0f, 0.0f, 0.0f), m_Inited(false)
	{
		m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
		{
			VertexBufferLayout layout;
			layout.Push(GL_FLOAT, 2);
			layout.Push(GL_FLOAT, 2);
			m_VAO.AddBuffer(*m_VBO, layout);
		}
		m_IBO = std::make_unique<IndexBuffer>(indice, 6);
		m_Shader = std::make_unique<Shader>("texture");

		m_Proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f);
		m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	}

	TestTexture2D::~TestTexture2D()
	{

	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{

	}

	void TestTexture2D::OnRender()
	{
		if (!m_Inited) return;
		m_Renderer.Clear();
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
		m_Shader->SetUniformMat4f("u_MVP", m_Proj * m_View * model);
		m_Renderer.Draw(m_VAO, *m_IBO, *m_Shader);
	}

	void TestTexture2D::OnGUI()
	{
		if (!m_Inited)
		{
			ImGui::InputText("Input a Texture Name", m_TextureName, IM_ARRAYSIZE(m_TextureName));
			if (ImGui::Button("Create Texture"))
			{
				std::string path = resPath + m_TextureName;
				std::cout << path << std::endl;
				m_CreateTexture(path);
			}
		}
		else
		{
			ImGui::SliderFloat3("Translation", &m_Translation.x, -2.0f, 2.0f);
		}
	}

	void TestTexture2D::m_CreateTexture(const std::string& path)
	{
		m_Shader->Bind();
		m_Texture = std::make_unique<Texture>(path);
		m_Texture->Bind(0);
		m_Shader->SetUniform1i("u_Texture", 0);

		m_Inited = true;
	}
}