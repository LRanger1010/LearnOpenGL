#pragma once
#include "Test.h"
#include "FrameBuffer.h"
#include "geometry/Cube.h"
#include "geometry/Quad.h"

namespace test {
	class Test3DModel : public Test
	{
	public:
		Test3DModel();
		~Test3DModel();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnGUI() override;

	private:
		std::unique_ptr<FrameBuffer> m_FBO;
		std::unique_ptr<Cube> m_Cube;
		std::unique_ptr<Quad> m_Quad;
	};
}