#include "pch.h"
#include "TestClearColor.h"
#include "Renderer.h"

namespace test {

	TestClearColor::TestClearColor()
		:m_ClearColor{0.2f,0.3f,0.8f,1.0f}
	{

	}

	TestClearColor::~TestClearColor()
	{
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColor::OnUpdate(float deltaTime)
	{

	}

	void TestClearColor::OnRender()
	{
		GLCALL(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColor::OnGUI()
	{
		ImGui::Text("Pick a Color!");
		ImGui::ColorEdit4("clear color", m_ClearColor);
		Test::OnGUI();
	}

}