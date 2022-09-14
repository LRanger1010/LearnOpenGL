#pragma once
#include "Test.h"
#include "Model.h"
#include "Light.h"
#include "geometry/Skybox.h"

namespace test
{
	class TestModel : public Test
	{
	public:
		TestModel();
		~TestModel();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnGUI() override;
	private:
		std::unique_ptr<Model> m_Model;
		std::unique_ptr<Shader> m_Shader;
		char m_ModelName[128];
		bool m_IsModelImported;
		glm::mat4 m_MatModel;
		glm::mat4 m_MVP;
		DirLight m_DirLight;
		PointLight m_PointLights[2];
		SpotLight m_SpotLight;
		std::unique_ptr<Shader> m_StencilShader;
		bool m_StencilTestOn;
		std::unique_ptr<Skybox> m_Skybox;
		bool m_Reflection;
		bool m_Refraction;
	private:
		void ImportModel(const std::string& path);
	};
}