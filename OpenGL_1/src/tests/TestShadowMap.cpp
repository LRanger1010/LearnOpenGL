#include "pch.h"
#include "TestShadowMap.h"
#include "camera/Camera.h"

namespace test {

	static const unsigned int SHADOW_WIDTH = 1024;
	static const unsigned int SHADOW_HEIGHT = 1024;
	static const std::string SHADOW_SHADER = "ShadowMap";
	static const std::string DEPTH_SHADER = "DepthMap";

	TestShadowMap::TestShadowMap()
		:m_ShadowOn(false)
	{
		m_DepthFBO = std::make_unique<FrameBuffer>(SHADOW_WIDTH, SHADOW_HEIGHT);
		m_DepthFBO->AttachTextureDepth();
		m_DepthFBO->SetBufferTarget(GL_NONE);
		m_DepthFBO->Unbind();

		m_Plane = std::make_unique<Plane>();
		m_Cube = std::make_unique<Cube>();

		m_DirLight.direction = glm::vec3(2.0f, -4.0f, 1.0f);
		m_DirLight.view = glm::lookAt(-m_DirLight.direction, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		m_DirLightProj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);

		m_DepthShader = std::make_shared<Shader>(DEPTH_SHADER);
		m_ShadowShader = std::make_shared<Shader>(SHADOW_SHADER);
	}

	TestShadowMap::~TestShadowMap()
	{

	}

	void TestShadowMap::OnUpdate(float deltaTime)
	{
		m_Plane->Update();
		m_Cube->Update();
	}

	void TestShadowMap::OnRender()
	{
		GLCALL(glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT));
		m_DepthFBO->Bind();
		GLCALL(glClear(GL_DEPTH_BUFFER_BIT));
		m_DepthShader->Bind();
		glm::mat4 lightMatrix = m_DirLightProj * m_DirLight.view;
		m_DepthShader->SetUniformMat4f("u_LightMatrix", lightMatrix);

		m_DepthShader->SetUniformMat4f("u_Model", m_Plane->GetModelMatrix());
		m_Plane->Draw(*m_DepthShader);

		m_DepthShader->SetUniformMat4f("u_Model", m_Cube->GetModelMatrix());
		m_Cube->Draw(*m_DepthShader);

		m_DepthFBO->Unbind();
		GLCALL(glViewport(0, 0, 1200, 900));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		m_ShadowShader->Bind();
		m_ShadowShader->SetUniform3fv("u_ViewPos", CAMERA_POS);
		m_ShadowShader->SetUniform1i("u_ShadowCast", (int)m_ShadowOn);
		m_ShadowShader->SetUniformMat4f("u_LightMatrix", lightMatrix);
		m_ShadowShader->SetUniform3fv("dirLight.ambient", m_DirLight.ambient);
		m_ShadowShader->SetUniform3fv("dirLight.diffuse", m_DirLight.diffuse);
		m_ShadowShader->SetUniform3fv("dirLight.specular", m_DirLight.specular);
		m_ShadowShader->SetUniform3fv("dirLight.dir", m_DirLight.direction);
		m_ShadowShader->SetUniform1i("material.diffuse", 0);
		m_ShadowShader->SetUniform1i("material.shadowMap", 1);
		m_ShadowShader->SetUniform1f("material.shininess", 32.0f);

		m_ShadowShader->SetUniformMat4f("u_Model", m_Plane->GetModelMatrix());
		m_ShadowShader->SetUniformMat4f("u_MVP", MATRIX_VP * m_Plane->GetModelMatrix());
		m_Plane->BindImage(0);
		unsigned int depthTex = m_DepthFBO->GetTextureDepthBuffer();
		m_Plane->Bind(depthTex, 1);
		m_Plane->Draw(*m_ShadowShader);

		m_ShadowShader->SetUniformMat4f("u_Model", m_Cube->GetModelMatrix());
		m_ShadowShader->SetUniformMat4f("u_MVP", MATRIX_VP * m_Cube->GetModelMatrix());
		m_Cube->BindImage(0);
		m_Cube->Bind(depthTex, 1);
		m_Cube->Draw(*m_ShadowShader);
	}

	void TestShadowMap::OnGUI()
	{
		ImGui::Checkbox("Shadow Cast", &m_ShadowOn);
	}

}