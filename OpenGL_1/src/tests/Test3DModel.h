#pragma once
#include "Test.h"
#include "FrameBuffer.h"
#include "geometry/Cube.h"
#include "postProcess/ScreenMask.h"

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
		std::unique_ptr<ScreenMask> m_ScreenMask;
		std::shared_ptr<Shader> m_CubeShader;
		std::unique_ptr<Texture> m_ScreenTex;
	};
}