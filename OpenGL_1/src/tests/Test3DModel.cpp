#include "Test3DModel.h"
#include "VertexBufferLayout.h"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

	static const float vertices[] = {
		//position	  //texture coord
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,	//0
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,	//1
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f,		//2
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,	//3
	};

	static const unsigned int indice[] = {
		0, 1, 2,
		2, 3, 0,
	};

	Test3DModel::Test3DModel()
	{
		m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
		{
			VertexBufferLayout layout;
			layout.Push(GL_FLOAT, 3);
			layout.Push(GL_FLOAT, 2);
			m_VAO.AddBuffer(*m_VBO, layout);
		}
		m_IBO = std::make_unique<IndexBuffer>(indice, 6);
		m_Shader = std::make_unique<Shader>("texture");

		glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		// 注意，我们将矩阵向我们要进行移动场景的反方向移动。
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 /(float)600, 0.1f, 100.0f);
		m_MVP = projection * view * model;

		m_Shader->Bind();
		m_Tex = std::make_unique<Texture>("res/textures/cherno.jpg");
		m_Tex->Bind(0);
		m_Shader->SetUniformMat4f("u_MVP", m_MVP);
		m_Shader->SetUniform1i("u_Texture", 0);
	}

	Test3DModel::~Test3DModel()
	{

	}

	void Test3DModel::OnUpdate(float deltaTime)
	{

	}

	void Test3DModel::OnRender()
	{
		m_Renderer.Clear();
		m_Renderer.Draw(m_VAO, *m_IBO, *m_Shader);
	}

	void Test3DModel::OnGUI()
	{

	}

}