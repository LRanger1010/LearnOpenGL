#pragma once
#include "Test.h"
#include "FrameBuffer.h"
#include "geometry/Plane.h"
#include "geometry/Cube.h"
#include "Light.h"

namespace test {
	class TestShadowMap : public Test
	{
	public:
		TestShadowMap();
		~TestShadowMap();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnGUI() override;

	private:
		std::unique_ptr<FrameBuffer> m_DepthFBO;
		std::unique_ptr<Shader> m_DepthShader;
		std::unique_ptr<Shader> m_DepthCubemapShader;
		std::unique_ptr<Shader> m_ShadowShader;
		std::unique_ptr<Plane> m_Plane;
		std::unique_ptr<Cube> m_Cube;
		DirLight m_DirLight;
		glm::mat4 m_DirLightProj;
		PointLight m_PointLight;
		glm::mat4 m_PointLightProj;
		std::vector<glm::mat4> m_ShadowTransforms;
		bool m_ShadowOn;
	};
}
