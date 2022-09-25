#include "pch.h"
#include "TestGPUInstancing.h"
#include "camera/Camera.h"
#include "VertexBufferLayout.h"
#include <stdlib.h>

namespace test {

	static const unsigned int amount = 10000;
	static const float radius = 50.0f;
	static const float offset = 5.0f;
	static const std::string planetPath = "res/model/planet/planet.obj";
	static const std::string rockPath = "res/model/rock/rock.obj";

	TestGPUInstancing::TestGPUInstancing()
	{
		srand((unsigned int)glfwGetTime());
		m_Planet = std::make_unique<Model>(planetPath);
		m_Rock = std::make_unique<Model>(rockPath);
		m_Shader = std::make_unique<Shader>("NormalLight");
		m_InstancedShader = std::make_unique<Shader>("GPUInstancing");
		for (unsigned int i = 0; i < amount; i++)
		{
			float angle = (float)i / (float)amount * 360.0f;
			float displacement = (rand() % (int)(2 * offset * 100 + 1)) / 100.0f - offset;
			float x = glm::sin(angle) * radius + displacement;
			displacement = (rand() % (int)(2 * offset * 100 + 1)) / 100.0f - offset;
			float y = displacement * 0.4f;
			displacement = (rand() % (int)(2 * offset * 100 + 1)) / 100.0f - offset;
			float z = glm::cos(angle) * radius + displacement;
			glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));

			float scale = (rand() % 21) / 100.0f + 0.05f;
			model = glm::scale(model, glm::vec3(scale));

			float rotAngle = (float)(rand() % 360);
			model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
			m_ModelMatrices.emplace_back(model);
		}
		m_ModelMatricesVBO = std::make_unique<VertexBuffer>(&m_ModelMatrices[0], m_ModelMatrices.size() * sizeof(glm::mat4));
		{
			VertexBufferLayout layout;
			for (int i = 0; i < 4; i++)
			{
				layout.Push(GL_FLOAT, 4);
			}
			m_Rock->BindVertexAttrib(*m_ModelMatricesVBO, layout);
		}
	}

	TestGPUInstancing::~TestGPUInstancing()
	{

	}

	void TestGPUInstancing::OnUpdate(float deltaTime)
	{
		
	}

	void TestGPUInstancing::OnRender()
	{
		m_Shader->Bind();
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f));
		m_Shader->SetUniformMat4f("u_Model", model);
		m_Shader->SetUniformMat4f("u_View", MATRIX_VIEW);
		m_Shader->SetUniformMat4f("u_Proj", MATRIX_PROJ);
		m_Shader->SetUniformMat4f("u_NormalMatrix", glm::transpose(glm::inverse(model)));
		m_Shader->SetUniform3fv("u_ViewPos", CAMERA_POS);
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
		m_Planet->Draw(*m_Shader);

		m_InstancedShader->Bind();
		m_InstancedShader->SetUniformMat4f("u_View", MATRIX_VIEW);
		m_InstancedShader->SetUniformMat4f("u_Proj", MATRIX_PROJ);
		m_InstancedShader->SetUniform3fv("u_ViewPos", CAMERA_POS);
		m_InstancedShader->SetUniform3fv("dirLight.ambient", m_DirLight.ambient);
		m_InstancedShader->SetUniform3fv("dirLight.diffuse", m_DirLight.diffuse);
		m_InstancedShader->SetUniform3fv("dirLight.specular", m_DirLight.specular);
		m_InstancedShader->SetUniform3fv("dirLight.dir", m_DirLight.direction);

		m_InstancedShader->SetUniform3fv("pointLights[0].ambient", m_PointLights[0].ambient);
		m_InstancedShader->SetUniform3fv("pointLights[0].diffuse", m_PointLights[0].diffuse);
		m_InstancedShader->SetUniform3fv("pointLights[0].specular", m_PointLights[0].specular);
		m_InstancedShader->SetUniform3fv("pointLights[0].pos", m_PointLights[0].position);
		m_InstancedShader->SetUniform1f("pointLights[0].constant", m_PointLights[0].constant);
		m_InstancedShader->SetUniform1f("pointLights[0].linear", m_PointLights[0].linear);
		m_InstancedShader->SetUniform1f("pointLights[0].quadratic", m_PointLights[0].quadratic);

		m_InstancedShader->SetUniform3fv("pointLights[1].ambient", m_PointLights[1].ambient);
		m_InstancedShader->SetUniform3fv("pointLights[1].diffuse", m_PointLights[1].diffuse);
		m_InstancedShader->SetUniform3fv("pointLights[1].specular", m_PointLights[1].specular);
		m_InstancedShader->SetUniform3fv("pointLights[1].pos", m_PointLights[1].position);
		m_InstancedShader->SetUniform1f("pointLights[1].constant", m_PointLights[1].constant);
		m_InstancedShader->SetUniform1f("pointLights[1].linear", m_PointLights[1].linear);
		m_InstancedShader->SetUniform1f("pointLights[1].quadratic", m_PointLights[1].quadratic);
		m_Rock->DrawInstanced(*m_InstancedShader, amount);
		
		//gpu instancing off
		/*for (unsigned int i = 0; i < amount; i++)
		{
			glm::mat4 rockModel = m_ModelMatrices[i];
			m_Shader->SetUniformMat4f("u_Model", rockModel);
			m_Shader->SetUniformMat4f("u_NormalMatrix", glm::transpose(glm::inverse(rockModel)));
			m_Rock->Draw(*m_Shader);
		}*/
	}

	void TestGPUInstancing::OnGUI()
	{
		ImGui::SliderFloat3("pointLight1 position", &m_PointLights[0].position.x, -20.0f, 20.0f);
		ImGui::SliderFloat3("pointLight2 position", &m_PointLights[1].position.x, -20.0f, 20.0f);
	}

}