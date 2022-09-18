#pragma once
#include "Test.h"
#include "Model.h"

namespace test {
	class TestGPUInstancing : public Test
	{
	public:
		TestGPUInstancing();
		~TestGPUInstancing();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnGUI() override;

	private:
		std::unique_ptr<Model> m_Planet;
		std::unique_ptr<Model> m_Rock;
	};
}