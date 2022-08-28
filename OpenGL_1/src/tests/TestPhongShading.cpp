#include "TestPhongShading.h"
#include "VertexBufferLayout.h"
#include "glm/gtc/matrix_transform.hpp"
#include "camera/Camera.h"

namespace test
{

	static const unsigned int MaxQuadCount = 6;
	static const unsigned int MaxVertexCount = 4 * MaxQuadCount;
	static const unsigned int MaxIndexCount = 6 * MaxQuadCount;

	static const float vertices[] = {
		//position			//normal
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	//0
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 	//1
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	//2
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	//3

		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,	//4
		0.5f, -0.5f, -1.0f, 1.0f, 0.0f, 0.0f,	//5
		0.5f, 0.5f, -1.0f, 1.0f, 0.0f, 0.0f,	//6
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,	//7

		-0.5f, -0.5f, -1.0f, 0.0f, 0.0f, -1.0f,	//8
		0.5f, -0.5f, -1.0f, 0.0f, 0.0f, -1.0f,	//9
		0.5f, 0.5f, -1.0f, 0.0f, 0.0f, -1.0f,	//10
		-0.5f, 0.5f, -1.0f, 0.0f, 0.0f, -1.0f,	//11

		-0.5f, -0.5f, -1.0f, -1.0f, 0.0f, 0.0f,	//12
		-0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f,	//13
		-0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f,	//14
		-0.5f, 0.5f, -1.0f, -1.0f, 0.0f, 0.0f,	//15

		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,	//16
		0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,	//17
		0.5f, 0.5f, -1.0f, 0.0f, 1.0f, 0.0f,	//18
		-0.5f, 0.5f, -1.0f, 0.0f, 1.0f, 0.0f,	//19

		-0.5f, -0.5f, -1.0f, 0.0f, -1.0f, 0.0f,	//20
		0.5f, -0.5f, -1.0f, 0.0f, -1.0f, 0.0f,	//21
		0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f,	//22
		-0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f,	//23
	};

	TestPhoneShading::TestPhoneShading()
	{
		m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
		{
			VertexBufferLayout layout;
			layout.Push(GL_FLOAT, 3);
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
		m_Shader = std::make_unique<Shader>("BlinnPhong");
	}

	TestPhoneShading::~TestPhoneShading()
	{

	}

	void TestPhoneShading::OnUpdate(float deltaTime)
	{
		m_Shader->Bind();
		m_Shader->SetUniform3fv("material.ambient", m_Material.ambient);
		m_Shader->SetUniform3fv("material.diffuse", m_Material.diffuse);
		m_Shader->SetUniform3fv("material.specular", m_Material.specular);
		m_Shader->SetUniform1f("material.shininess", m_Material.shininess);
		m_Shader->SetUniform3fv("light.ambient", m_Light.ambient);
		m_Shader->SetUniform3fv("light.diffuse", m_Light.diffuse);
		m_Shader->SetUniform3fv("light.specular", m_Light.specular);
		m_Shader->SetUniform3fv("light.pos", m_Light.position);
		glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians((float)glfwGetTime() * 50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		m_MVP = MATRIX_VP * model;
		m_Shader->SetUniformMat4f("u_Model", model);
		m_Shader->SetUniformMat4f("u_MVP", m_MVP);
		m_Shader->SetUniform3fv("viewPos", CAMERA_POS);
	}

	void TestPhoneShading::OnRender()
	{
		m_Renderer.Draw(m_VAO, *m_IBO, *m_Shader);
	}

	void TestPhoneShading::OnGUI()
	{
		ImGui::ColorEdit3("material ambient", &m_Material.ambient.x);
		ImGui::ColorEdit3("material diffuse", &m_Material.diffuse.x);
		ImGui::ColorEdit3("material specular", &m_Material.specular.x);
		ImGui::SliderFloat3("light position", &m_Light.position.x, -2.0f, 2.0f);
		ImGui::ColorEdit3("light ambient", &m_Light.ambient.x);
		ImGui::ColorEdit3("light diffuse", &m_Light.diffuse.x);
		ImGui::ColorEdit3("light specular", &m_Light.specular.x);
	}

}