#include "pch.h"
#include "TestModel.h"
#include "camera/Camera.h"

namespace test
{
	const static std::string modelDir = "res/model/";

	TestModel::TestModel()
		:m_ModelName(""), m_IsModelImported(false)
	{

	}

	TestModel::~TestModel()
	{

	}

	void TestModel::OnUpdate(float deltaTime)
	{
		if (m_IsModelImported)
		{
			m_SpotLight.position = CAMERA_POS;
			m_SpotLight.direction = CAMERA_DIR;

			m_Shader->Bind();
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
	}

	void TestModel::OnRender()
	{
		if (m_Model)
		{
			m_Model->Draw(*m_Shader);
		}
	}

	void TestModel::OnGUI()
	{
		if (!m_IsModelImported)
		{
			if (ImGui::Button("nano suit"))
			{
				ImportModel(modelDir + "nanosuit/nanosuit.obj");
			}
			ImGui::InputText("Input a Model Path", m_ModelName, IM_ARRAYSIZE(m_ModelName));
			if (ImGui::Button("Import Model"))
			{
				std::string path = modelDir + m_ModelName;
				ImportModel(path);
			}
		}
		else
		{
			ImGui::SliderFloat3("pointLight1 position", &m_PointLights[0].position.x, -20.0f, 20.0f);
			ImGui::SliderFloat3("pointLight2 position", &m_PointLights[1].position.x, -20.0f, 20.0f);
		}
	}
	void TestModel::ImportModel(const std::string& path)
	{
		m_Model = std::make_unique<Model>(path);
		m_Shader = std::make_unique<Shader>("Assimp");
		m_IsModelImported = true;
	}
}