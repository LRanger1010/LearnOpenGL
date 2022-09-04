#pragma once
#include "Test.h"
#include "Model.h"

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
	private:
		void ImportModel(const std::string& path);
	};
}