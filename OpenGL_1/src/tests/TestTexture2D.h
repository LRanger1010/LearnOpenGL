#pragma once
#include "Test.h"
#include "Texture.h"
#include "Renderer.h"
#include "Shader.h"
#include <memory>

namespace test {

	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnGUI() override;

	private:
		char m_TextureName[128] = "";
		Renderer m_Renderer;
		VertexArray m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		glm::mat4 m_Proj;
		glm::mat4 m_View;
		glm::vec3 m_Translation;
		bool m_Inited;

		void m_CreateTexture(const std::string& path);
	};
}