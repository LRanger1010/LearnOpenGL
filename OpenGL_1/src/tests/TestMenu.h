#pragma once
#include "Test.h"

namespace test {
	class TestMenu : public Test
	{
	public:
		TestMenu();
		~TestMenu();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnGUI() override;

		void StartTest(int flag);
		void EndTest();

	private:
		Test* m_Test = nullptr;
		int m_TestFlag = 0;
	};
}