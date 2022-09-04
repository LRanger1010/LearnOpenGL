#include "pch.h"
#include "TestModel.h"

namespace test
{
	const static std::string modelDir = "res/model/";

	TestModel::TestModel()
		:m_ModelName(""), m_IsModelImported(false)
	{

	}

	TestModel::~TestModel()
	{

	}

	void TestModel::OnUpdate(float deltaTime)
	{

	}

	void TestModel::OnRender()
	{
		if (m_Model)
		{
			m_Model->Draw(*m_Shader);
		}
	}

	void TestModel::OnGUI()
	{
		if (!m_IsModelImported)
		{
			ImGui::InputText("Input a Model Path", m_ModelName, IM_ARRAYSIZE(m_ModelName));
			if (ImGui::Button("Import Model"))
			{
				std::string path = modelDir + m_ModelName;
				ImportModel(path);
			}
		}
	}
	void TestModel::ImportModel(const std::string& path)
	{
		m_Model = std::make_unique<Model>(path);
		m_Shader = std::make_unique<Shader>("Assimp");
		m_IsModelImported = true;
	}
}