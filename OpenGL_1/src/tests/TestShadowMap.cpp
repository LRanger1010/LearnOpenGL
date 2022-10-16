#include "pch.h"
#include "TestShadowMap.h"
#include "camera/Camera.h"

namespace test {

	static const unsigned int SHADOW_WIDTH = 1024;
	static const unsigned int SHADOW_HEIGHT = 1024;
	static const std::string SHADOW_SHADER = "ShadowMap";
	static const std::string DEPTH_SHADER = "DepthMap";
	static const std::string DEPTH_CUBEMAP_SHADER = "DepthCubemap";

	TestShadowMap::TestShadowMap()
		:m_ShadowOn(false), m_FarPlane(25.0f)
	{
		m_DepthFBO = std::make_unique<FrameBuffer>(SHADOW_WIDTH, SHADOW_HEIGHT);
		m_DepthFBO->CreateTextureDepth();
		m_DepthFBO->SetBufferTarget(GL_NONE);
		m_DepthFBO->Unbind();
		m_DepthCubemap = std::make_unique<CubeMap>(GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT);

		m_Plane = std::make_unique<Plane>();
		m_Cube = std::make_unique<Cube>();
		m_Cube->Rotate(glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		m_DirLight.direction = glm::vec3(2.0f, -4.0f, 1.0f);
		m_DirLight.view = glm::lookAt(-m_DirLight.direction, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		m_DirLightProj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);

		m_PointLight.position = glm::vec3(0.0f);
		m_PointLightProj = glm::perspective(glm::radians(90.0f), 1200.0f / 900.0f, 1.0f, m_FarPlane);
		m_ShadowTransforms.emplace_back(m_PointLightProj * glm::lookAt(m_PointLight.position, m_PointLight.position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		m_ShadowTransforms.emplace_back(m_PointLightProj * glm::lookAt(m_PointLight.position, m_PointLight.position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		m_ShadowTransforms.emplace_back(m_PointLightProj * glm::lookAt(m_PointLight.position, m_PointLight.position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
		m_ShadowTransforms.emplace_back(m_PointLightProj * glm::lookAt(m_PointLight.position, m_PointLight.position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
		m_ShadowTransforms.emplace_back(m_PointLightProj * glm::lookAt(m_PointLight.position, m_PointLight.position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		m_ShadowTransforms.emplace_back(m_PointLightProj * glm::lookAt(m_PointLight.position, m_PointLight.position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

		m_DepthShader = std::make_unique<Shader>(DEPTH_SHADER);
		m_ShadowShader = std::make_unique<Shader>(SHADOW_SHADER);
		m_DepthCubemapShader = std::make_unique<Shader>(DEPTH_CUBEMAP_SHADER);
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
		m_DepthFBO->AttachTextureDepth();
		GLCALL(glClear(GL_DEPTH_BUFFER_BIT));
		m_DepthShader->Bind();
		glm::mat4 lightMatrix = m_DirLightProj * m_DirLight.view;
		m_DepthShader->SetUniformMat4f("u_LightMatrix", lightMatrix);
		m_DepthShader->SetUniformMat4f("u_Model", m_Plane->GetModelMatrix());
		m_Plane->Draw(*m_DepthShader);
		m_DepthShader->SetUniformMat4f("u_Model", m_Cube->GetModelMatrix());
		m_Cube->Draw(*m_DepthShader);
		unsigned int depthTex = m_DepthFBO->GetTextureDepthBuffer();

		unsigned int cubemapDepthTex = m_DepthCubemap->GetRenderID();
		m_DepthFBO->AttachCubeMapDepth(cubemapDepthTex);
		GLCALL(glClear(GL_DEPTH_BUFFER_BIT));
		m_DepthCubemapShader->Bind();
		for (unsigned int i = 0; i < 6; i++)
		{
			m_DepthCubemapShader->SetUniformMat4f("lightMatrix[" + std::to_string(i) + "]", m_ShadowTransforms[i]);
		}
		m_DepthCubemapShader->SetUniform3fv("lightPos", m_PointLight.position);
		m_DepthCubemapShader->SetUniform1f("farPlane", m_FarPlane);
		m_DepthCubemapShader->SetUniformMat4f("u_Model", m_Plane->GetModelMatrix());
		m_Plane->Draw(*m_DepthCubemapShader);
		m_DepthCubemapShader->SetUniformMat4f("u_Model", m_Cube->GetModelMatrix());
		m_Cube->Draw(*m_DepthCubemapShader);

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
		m_ShadowShader->SetUniform3fv("pointLight.ambient", m_PointLight.ambient);
		m_ShadowShader->SetUniform3fv("pointLight.diffuse", m_PointLight.diffuse);
		m_ShadowShader->SetUniform3fv("pointLight.specular", m_PointLight.specular);
		m_ShadowShader->SetUniform3fv("pointLight.pos", m_PointLight.position);
		m_ShadowShader->SetUniform1f("pointLight.constant", m_PointLight.constant);
		m_ShadowShader->SetUniform1f("pointLight.linear", m_PointLight.linear);
		m_ShadowShader->SetUniform1f("pointLight.quadratic", m_PointLight.quadratic);
		m_ShadowShader->SetUniform1i("material.diffuse", 0);
		m_ShadowShader->SetUniform1i("material.shadowMap", 1);
		m_ShadowShader->SetUniform1i("material.shadowCubemap", 2);
		m_ShadowShader->SetUniform1f("material.shininess", 32.0f);
		m_ShadowShader->SetUniform1f("farPlane", m_FarPlane);

		m_ShadowShader->SetUniformMat4f("u_Model", m_Plane->GetModelMatrix());
		m_ShadowShader->SetUniformMat4f("u_MVP", MATRIX_VP * m_Plane->GetModelMatrix());
		m_Plane->BindImage(0);
		m_Plane->Bind(depthTex, 1);
		m_Plane->Bind(cubemapDepthTex, 2);
		m_Plane->Draw(*m_ShadowShader);

		m_ShadowShader->SetUniformMat4f("u_Model", m_Cube->GetModelMatrix());
		m_ShadowShader->SetUniformMat4f("u_MVP", MATRIX_VP * m_Cube->GetModelMatrix());
		m_Cube->BindImage(0);
		m_Cube->Bind(depthTex, 1);
		m_Cube->Bind(cubemapDepthTex, 2);
		m_Cube->Draw(*m_ShadowShader);
	}

	void TestShadowMap::OnGUI()
	{
		ImGui::Checkbox("Shadow Cast", &m_ShadowOn);
	}

}