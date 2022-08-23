#pragma once
#include "Test.h"
#include "Renderer.h"
#include "glm/glm.hpp"
#include <memory>

namespace test
{
	class TestPhoneShading : public Test
	{
	public:
		TestPhoneShading();
		~TestPhoneShading();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnGUI() override;

	private:
		Renderer m_Renderer;
		VertexArray m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_Shader;
		glm::mat4 m_MVP;
		glm::vec3 m_lightPos;
	};
}


