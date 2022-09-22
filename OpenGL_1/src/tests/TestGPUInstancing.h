#pragma once
#include "Test.h"
#include "Model.h"
#include "Light.h"

namespace test {
	class TestGPUInstancing : public Test
	{
	public:
		TestGPUInstancing();
		~TestGPUInstancing();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnGUI() override;

	private:
		std::unique_ptr<Model> m_Planet;
		std::unique_ptr<Model> m_Rock;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Shader> m_InstancedShader;
		std::vector<glm::mat4> m_ModelMatrices;
		std::unique_ptr<VertexBuffer> m_ModelMatricesVBO;
		DirLight m_DirLight;
		PointLight m_PointLights[2];
	};
}