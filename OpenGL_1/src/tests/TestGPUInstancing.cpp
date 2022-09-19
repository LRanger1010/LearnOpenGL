#include "pch.h"
#include "TestGPUInstancing.h"
#include <stdlib.h>

namespace test {

	static const unsigned int amount = 1000;
	static const float radius = 50.0f;
	static const float offset = 2.5f;
	static const std::string planetPath = "res/model/planet/planet.obj";
	static const std::string rockPath = "res/model/rock/rock.obj";

	TestGPUInstancing::TestGPUInstancing()
	{
		srand(glfwGetTime());
		m_Planet = std::make_unique<Model>(planetPath);
		m_Rock = std::make_unique<Model>(rockPath);
		m_Shader = std::make_unique<Shader>("Assimp");
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

			float rotAngle = rand() % 360;
			model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
			m_ModelMatrices.emplace_back(model);
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

	}

	void TestGPUInstancing::OnGUI()
	{

	}

}