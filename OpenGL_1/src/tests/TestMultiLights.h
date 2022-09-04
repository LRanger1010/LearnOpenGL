#pragma once
#include "Test.h"
#include "Renderer.h"
#include "Material.h"
#include "Light.h"
#include "Image.h"

namespace test
{
	class TestMultiLights : public Test
	{
	public:
		TestMultiLights();
		~TestMultiLights();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnGUI() override;

	private:
		Renderer m_Renderer;
		VertexArray m_VAO;
		std::unique_ptr<VertexBuffer> m_VBO;
		std::unique_ptr<IndexBuffer> m_IBO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Image> m_MainTex;
		std::unique_ptr<Image> m_specTex;
		glm::mat4 m_MVP;
		Material m_Material;
		DirLight m_DirLight;
		PointLight m_PointLights[2];
		SpotLight m_SpotLight;
	};
}