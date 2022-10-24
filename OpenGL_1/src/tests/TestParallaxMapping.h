#pragma once
#include "Test.h"
#include "geometry/Quad.h"

namespace test {
	class TestParallaxMapping : public Test
	{
	public:
		TestParallaxMapping();
		~TestParallaxMapping();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnGUI() override;

	private:
		std::unique_ptr<Quad> m_Quad;
		std::unique_ptr<Shader> m_Shader;
	};
}
