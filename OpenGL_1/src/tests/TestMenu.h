#pragma once
#include "Test.h"
#include "TestClearColor.h"
#include "TestTexture2D.h"
#include "TestBatchRenderingTexture2D.h"
#include <vector>
#include <functional>
#include <string>

namespace test {
	class TestMenu : public Test
	{
	public:
		TestMenu();
		~TestMenu();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnGUI() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			m_TestList.push_back(std::make_pair(name, []() { return new T; }));
		}

	private:
		Test* m_Test = nullptr;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_TestList;
	};
}