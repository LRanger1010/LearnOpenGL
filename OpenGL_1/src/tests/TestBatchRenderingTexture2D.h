#pragma once
#include "Test.h"
#include "Renderer.h"
#include "Image.h"
#include "Shader.h"

namespace test {
	class TestBatchRenderingTexture2D : public Test
	{
	public:
		TestBatchRenderingTexture2D();
		~TestBatchRenderingTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnGUI() override;

	private:
		Renderer m_Renderer;
		VertexArray m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Image> m_Tex1;
		std::unique_ptr<Image> m_Tex2;
		glm::mat4 m_Proj;
	};
}