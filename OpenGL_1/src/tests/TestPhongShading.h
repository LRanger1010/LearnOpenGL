#pragma once
#include "Test.h"
#include "Renderer.h"
#include "material/MaterialData.h"
#include "Light.h"

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
		MaterialData m_Material;
		PointLight m_Light;
		bool m_IsBlinn;
	};
}


