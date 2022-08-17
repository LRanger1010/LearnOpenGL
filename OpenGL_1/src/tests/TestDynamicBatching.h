#pragma once
#include "Test.h"
#include "Renderer.h"
#include "Texture.h"
#include "Shader.h"
#include <memory>

namespace test {
	class TestDynamicBatching : public Test
	{
	public:
		TestDynamicBatching();
		~TestDynamicBatching();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnGUI() override;

	private:
		Renderer m_Renderer;
		VertexArray m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Tex1;
		std::unique_ptr<Texture> m_Tex2;
		glm::mat4 m_Proj;
		float m_x = -2.0f;
		float m_y = -1.5f;
	};
}