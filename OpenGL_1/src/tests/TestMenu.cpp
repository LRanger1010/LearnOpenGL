#include "TestMenu.h"
#include "TestClearColor.h"

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
		else
		{
			switch (m_TestFlag)
			{
			case 1:
				m_Test = new TestClearColor;
				break;
			default:
				break;
			}
		}
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
				EndTest();
		}
		else
		{
			if (ImGui::Button("1.Start TestClearColor"))
				StartTest(1);
			
		}
		
	}

	void TestMenu::StartTest(int flag)
	{
		m_TestFlag = flag;
	}

	void TestMenu::EndTest()
	{
		if (m_Test != nullptr)
		{
			delete m_Test;
			m_Test = nullptr;
			m_TestFlag = 0;
		}
	}

}