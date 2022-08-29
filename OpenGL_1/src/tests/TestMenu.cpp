#include "pch.h"
#include "TestMenu.h"

namespace test {

	TestMenu::TestMenu()
	{

	}

	TestMenu::~TestMenu()
	{

	}

	void TestMenu::OnUpdate(float deltaTime)
	{
		if (m_Test != nullptr)
			m_Test->OnUpdate(deltaTime);
	}

	void TestMenu::OnRender()
	{
		if (m_Test != nullptr)
			m_Test->OnRender();
	}

	void TestMenu::OnGUI()
	{
		if (m_Test != nullptr)
		{
			m_Test->OnGUI();
			if (ImGui::Button("Back"))
			{
				delete m_Test;
				m_Test = nullptr;
			}
		}
		else
		{
			for (auto& test : m_TestList)
			{
				if (ImGui::Button(test.first.c_str()))
					m_Test = test.second();
			}
			
		}
		
	}

}