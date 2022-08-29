#pragma once
#include "pch.h"
#include "Test.h"
#include "Renderer.h"
#include "Texture.h"

namespace test {
	class Test3DModel : public Test
	{
	public:
		Test3DModel();
		~Test3DModel();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnGUI() override;

	private:
		Renderer m_Renderer;
		VertexArray m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Tex;
		glm::mat4 m_MVP;
	};
}