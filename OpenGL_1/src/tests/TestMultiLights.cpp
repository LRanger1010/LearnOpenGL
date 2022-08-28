#include "TestMultiLights.h"
#include "VertexBufferLayout.h"
#include "glm/gtc/matrix_transform.hpp"
#include "camera/Camera.h"

namespace test
{
	static const unsigned int MaxQuadCount = 6;
	static const unsigned int MaxVertexCount = 4 * MaxQuadCount;
	static const unsigned int MaxIndexCount = 6 * MaxQuadCount;

	static const float vertices[] = {
		//position			//normal			//texCoords
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,	//0
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,	//1
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,	//2
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,	//3

		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	//4
		0.5f, -0.5f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,	//5
		0.5f, 0.5f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,	//6
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,	//7

		-0.5f, -0.5f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,	//8
		0.5f, -0.5f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,	//9
		0.5f, 0.5f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,	//10
		-0.5f, 0.5f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,	//11

		-0.5f, -0.5f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	//12
		-0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,	//13
		-0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,	//14
		-0.5f, 0.5f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,	//15

		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,	//16
		0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	//17
		0.5f, 0.5f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,	//18
		-0.5f, 0.5f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	//19

		-0.5f, -0.5f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,	//20
		0.5f, -0.5f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,	//21
		0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,	//22
		-0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,	//23
	};

	TestMultiLights::TestMultiLights()
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
		m_Shader = std::make_unique<Shader>("MultiLights");
		m_MainTex = std::make_unique<Texture>("res/textures/container2.png");
		m_specTex = std::make_unique<Texture>("res/textures/container2_specular.png");
		m_MainTex->Bind(m_Material.mainTex);
		m_specTex->Bind(m_Material.specTex);
	}

	TestMultiLights::~TestMultiLights()
	{

	}

	void TestMultiLights::OnUpdate(float deltaTime)
	{
		//TODO:set spotLight's pos and dir
		m_SpotLight.position = CAMERA_POS;
		m_SpotLight.direction = CAMERA_DIR;

		m_Shader->Bind();
		m_Shader->SetUniform3fv("material.ambient", m_Material.ambient);
		m_Shader->SetUniform3fv("material.diffuse", m_Material.diffuse);
		m_Shader->SetUniform3fv("material.specular", m_Material.specular);
		m_Shader->SetUniform1f("material.shininess", m_Material.shininess);
		m_Shader->SetUniform1i("material.mainTex", m_Material.mainTex);
		m_Shader->SetUniform1i("material.specTex", m_Material.specTex);

		m_Shader->SetUniform3fv("dirLight.ambient", m_DirLight.ambient);
		m_Shader->SetUniform3fv("dirLight.diffuse", m_DirLight.diffuse);
		m_Shader->SetUniform3fv("dirLight.specular", m_DirLight.specular);
		m_Shader->SetUniform3fv("dirLight.dir", m_DirLight.direction);

		m_Shader->SetUniform3fv("pointLights[0].ambient", m_PointLights[0].ambient);
		m_Shader->SetUniform3fv("pointLights[0].diffuse", m_PointLights[0].diffuse);
		m_Shader->SetUniform3fv("pointLights[0].specular", m_PointLights[0].specular);
		m_Shader->SetUniform3fv("pointLights[0].pos", m_PointLights[0].position);
		m_Shader->SetUniform1f("pointLights[0].constant", m_PointLights[0].constant);
		m_Shader->SetUniform1f("pointLights[0].linear", m_PointLights[0].linear);
		m_Shader->SetUniform1f("pointLights[0].quadratic", m_PointLights[0].quadratic);

		m_Shader->SetUniform3fv("pointLights[1].ambient", m_PointLights[1].ambient);
		m_Shader->SetUniform3fv("pointLights[1].diffuse", m_PointLights[1].diffuse);
		m_Shader->SetUniform3fv("pointLights[1].specular", m_PointLights[1].specular);
		m_Shader->SetUniform3fv("pointLights[1].pos", m_PointLights[1].position);
		m_Shader->SetUniform1f("pointLights[1].constant", m_PointLights[1].constant);
		m_Shader->SetUniform1f("pointLights[1].linear", m_PointLights[1].linear);
		m_Shader->SetUniform1f("pointLights[1].quadratic", m_PointLights[1].quadratic);

		m_Shader->SetUniform3fv("spotLight.ambient", m_SpotLight.ambient);
		m_Shader->SetUniform3fv("spotLight.diffuse", m_SpotLight.diffuse);
		m_Shader->SetUniform3fv("spotLight.specular", m_SpotLight.specular);
		m_Shader->SetUniform3fv("spotLight.pos", m_SpotLight.position);
		m_Shader->SetUniform3fv("spotLight.dir", m_SpotLight.direction);
		m_Shader->SetUniform1f("spotLight.cutOff", m_SpotLight.cutOff);
		m_Shader->SetUniform1f("spotLight.outterCutOff", m_SpotLight.outterCutOff);
		
		glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians((float)glfwGetTime() * 30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		m_MVP = MATRIX_VP * model;
		m_Shader->SetUniformMat4f("u_Model", model);
		m_Shader->SetUniformMat4f("u_NormalMatrix", glm::transpose(glm::inverse(model)));
		m_Shader->SetUniformMat4f("u_MVP", m_MVP);
		m_Shader->SetUniform3fv("viewPos", CAMERA_POS);
	}

	void TestMultiLights::OnRender()
	{
		m_Renderer.Draw(m_VAO, *m_IBO, *m_Shader);
	}

	void TestMultiLights::OnGUI()
	{
		ImGui::ColorEdit3("material ambient", &m_Material.ambient.x);
		ImGui::ColorEdit3("material diffuse", &m_Material.diffuse.x);
		ImGui::ColorEdit3("material specular", &m_Material.specular.x);
		ImGui::SliderFloat3("pointLight1 position", &m_PointLights[0].position.x, -2.0f, 2.0f);
		ImGui::SliderFloat3("pointLight2 position", &m_PointLights[1].position.x, -2.0f, 2.0f);
	}

}