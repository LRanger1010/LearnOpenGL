#include "pch.h"
#include "TestModel.h"
#include "camera/Camera.h"

namespace test
{
	const static std::string modelDir = "res/model/";

	TestModel::TestModel()
		:m_ModelName(""), m_IsModelImported(false), m_StencilTestOn(false), m_Reflection(false), m_Refraction(false), m_VisualNormal(false)
	{
		m_Skybox = std::make_unique<Skybox>();
		m_MSFBO = std::make_unique<FrameBuffer>(1200, 900);
		m_MSFBO->AttachMultiSampleTextureColor(0, 4);
		m_MSFBO->AttachMultiSampleRenderBuffer(4);
		m_MSFBO->Unbind();
		
		m_IntermediateFBO = std::make_unique<FrameBuffer>(1200, 900);
		m_IntermediateScreenTex = std::make_unique<Texture>(1200, 900, GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_RGBA);
		m_IntermediateFBO->AttachTextureColor(m_IntermediateScreenTex->GetRenderID(), 0);
		m_IntermediateFBO->AttachRenderBuffer();
		m_IntermediateFBO->Unbind();
	}

	TestModel::~TestModel()
	{

	}

	void TestModel::OnUpdate(float deltaTime)
	{
		if (m_Skybox)
		{
			m_Skybox->Update();
		}
		if (m_IsModelImported)
		{
			if (m_ScreenMask)
			{
				m_ScreenMask->Update();
			}
			if (m_Reflection)
			{
				m_Shader->Bind();
				m_Shader->SetUniform1i("u_Skybox", 0);
			}
			else if (m_Refraction)
			{
				m_Shader->Bind();
				m_Shader->SetUniform1i("u_Skybox", 0);
				m_Shader->SetUniform1f("u_refractive_index", 1.0f / 1.52f);
			}
			else
			{
				m_SpotLight.position = CAMERA_POS;
				m_SpotLight.direction = CAMERA_DIR;

				m_Shader->Bind();
				m_Shader->SetUniform3fv("u_DirLight.ambient", m_DirLight.ambient);
				m_Shader->SetUniform3fv("u_DirLight.diffuse", m_DirLight.diffuse);
				m_Shader->SetUniform3fv("u_DirLight.specular", m_DirLight.specular);
				m_Shader->SetUniform3fv("u_DirLight.dir", m_DirLight.direction);

				m_Shader->SetUniform3fv("u_PointLights[0].ambient", m_PointLights[0].ambient);
				m_Shader->SetUniform3fv("u_PointLights[0].diffuse", m_PointLights[0].diffuse);
				m_Shader->SetUniform3fv("u_PointLights[0].specular", m_PointLights[0].specular);
				m_Shader->SetUniform3fv("u_PointLights[0].pos", m_PointLights[0].position);
				m_Shader->SetUniform1f("u_PointLights[0].constant", m_PointLights[0].constant);
				m_Shader->SetUniform1f("u_PointLights[0].linear", m_PointLights[0].linear);
				m_Shader->SetUniform1f("u_PointLights[0].quadratic", m_PointLights[0].quadratic);

				m_Shader->SetUniform3fv("u_PointLights[1].ambient", m_PointLights[1].ambient);
				m_Shader->SetUniform3fv("u_PointLights[1].diffuse", m_PointLights[1].diffuse);
				m_Shader->SetUniform3fv("u_PointLights[1].specular", m_PointLights[1].specular);
				m_Shader->SetUniform3fv("u_PointLights[1].pos", m_PointLights[1].position);
				m_Shader->SetUniform1f("u_PointLights[1].constant", m_PointLights[1].constant);
				m_Shader->SetUniform1f("u_PointLights[1].linear", m_PointLights[1].linear);
				m_Shader->SetUniform1f("u_PointLights[1].quadratic", m_PointLights[1].quadratic);

				m_Shader->SetUniform3fv("u_SpotLight.ambient", m_SpotLight.ambient);
				m_Shader->SetUniform3fv("u_SpotLight.diffuse", m_SpotLight.diffuse);
				m_Shader->SetUniform3fv("u_SpotLight.specular", m_SpotLight.specular);
				m_Shader->SetUniform3fv("u_SpotLight.pos", m_SpotLight.position);
				m_Shader->SetUniform3fv("u_SpotLight.dir", m_SpotLight.direction);
				m_Shader->SetUniform1f("u_SpotLight.cutOff", m_SpotLight.cutOff);
				m_Shader->SetUniform1f("u_SpotLight.outterCutOff", m_SpotLight.outterCutOff);
			}

			m_MatModel = glm::rotate(glm::mat4(1.0f), glm::radians((float)glfwGetTime() * 30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			m_MVP = MATRIX_VP * m_MatModel;
			m_Shader->SetUniformMat4f("u_Model", m_MatModel);
			m_Shader->SetUniformMat4f("u_NormalMatrix", glm::transpose(glm::inverse(m_MatModel)));
			m_Shader->SetUniformMat4f("u_MVP", m_MVP);
			m_Shader->SetUniform3fv("u_ViewPos", CAMERA_POS);
			auto materials = m_Model->GetMaterials();
			for (unsigned int i = 0; i < materials.size(); i++)
			{
				auto mat = materials[i];
				m_Shader->SetUniform3fv("material.ambient", mat.GetAmbient());
				m_Shader->SetUniform3fv("material.diffuse", mat.GetDiffuse());
				m_Shader->SetUniform3fv("material.specular", mat.GetSpecular());
				m_Shader->SetUniform1f("material.shininess", mat.GetShininess());
				auto texes = mat.GetTextures();
				unsigned int diffuseSlot = 0;
				unsigned int specularSlot = 0;
				unsigned int normalSlot = 0;
				for (unsigned int i = 0; i < texes.size(); i++)
				{
					std::string name = "material." + texes[i].GetType();
					if (texes[i].GetType() == "diffuse")
						name += std::to_string(diffuseSlot++);
					else if (texes[i].GetType() == "specular")
						name += std::to_string(specularSlot++);
					else if (texes[i].GetType() == "normal")
						name += std::to_string(normalSlot++);
					m_Shader->SetUniform1i(name, i);
				}
			}
		}
	}

	void TestModel::OnRender()
	{
		GLCALL(glEnable(GL_DEPTH_TEST));
		if (m_Model)
		{
			if (m_MSAAOn)
			{
				m_MSFBO->Bind();
				GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
			}

			if (m_StencilTestOn)
			{
				GLCALL(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));
				GLCALL(glStencilMask(0xFF));
				GLCALL(glStencilFunc(GL_ALWAYS, 1, 0xFF));
			}

			m_Model->Draw(*m_Shader);

			if (m_StencilTestOn)
			{
				m_Shader->Unbind();
				if (!m_StencilShader)
				{
					m_StencilShader = std::make_unique<Shader>("SingleColor");
				}
				m_MatModel = glm::scale(m_MatModel, glm::vec3(1.01f, 1.01f, 1.01f));
				m_MVP = MATRIX_VP * m_MatModel;
				m_StencilShader->Bind();
				m_StencilShader->SetUniformMat4f("u_MVP", m_MVP);
				GLCALL(glStencilMask(0x00));
				GLCALL(glStencilFunc(GL_NOTEQUAL, 1, 0xFF));
				m_Model->Draw(*m_StencilShader);
				GLCALL(glStencilMask(0xFF));
				GLCALL(glStencilFunc(GL_ALWAYS, 0, 0xFF));
			}
			
			if (m_VisualNormal)
			{
				m_Shader->Unbind();
				if (!m_VisualNormalShader)
				{
					m_VisualNormalShader = std::make_unique<Shader>("VisualNormal");
				}
				m_VisualNormalShader->Bind();
				m_VisualNormalShader->SetUniformMat4f("u_Model", m_MatModel);
				m_VisualNormalShader->SetUniformMat4f("u_View", MATRIX_VIEW);
				m_VisualNormalShader->SetUniformMat4f("u_Projection", MATRIX_PROJ);
				m_Model->Draw(*m_VisualNormalShader);
			}

			DrawSkybox();

			if (m_MSAAOn)
			{
				FrameBuffer::BlitFramebuffer(*m_MSFBO, *m_IntermediateFBO);
				m_MSFBO->Unbind();
				GLCALL(glDisable(GL_DEPTH_TEST));
				GLCALL(glClear(GL_COLOR_BUFFER_BIT));
				//unsigned int textureId = m_IntermediateFBO->GetTextureColorBuffer();
				m_ScreenMask->Draw(*m_IntermediateScreenTex, 0);
			}
		}
		else
			DrawSkybox();
	}

	void TestModel::OnGUI()
	{
		if (!m_IsModelImported)
		{
			if (ImGui::Button("nano suit"))
			{
				ImportModel(modelDir + "nanosuit/nanosuit.obj");
				m_ScreenMask = std::make_unique<ScreenMask>();
			}
			ImGui::InputText("Input a Model Path", m_ModelName, IM_ARRAYSIZE(m_ModelName));
			if (ImGui::Button("Import Model"))
			{
				std::string path = modelDir + m_ModelName;
				ImportModel(path);
			}
		}
		else
		{
			ImGui::SliderFloat3("pointLight1 position", &m_PointLights[0].position.x, -20.0f, 20.0f);
			ImGui::SliderFloat3("pointLight2 position", &m_PointLights[1].position.x, -20.0f, 20.0f);
			if (ImGui::Button("Stencil Test"))
			{
				m_StencilTestOn = !m_StencilTestOn;
			}
			if (ImGui::Button("Reflection"))
			{
				m_Reflection = !m_Reflection;
				m_Refraction = false;
				if (m_Reflection)
				{
					m_Shader = nullptr;
					m_Shader = std::make_unique<Shader>("Reflection");
				}
				else
				{
					m_Shader = nullptr;
					m_Shader = std::make_unique<Shader>("Assimp");
				}
			}
			if (ImGui::Button("Refraction"))
			{
				m_Refraction = !m_Refraction;
				m_Reflection = false;
				if (m_Refraction)
				{
					m_Shader = nullptr;
					m_Shader = std::make_unique<Shader>("Refraction");
				}
				else
				{
					m_Shader = nullptr;
					m_Shader = std::make_unique<Shader>("Assimp");
				}
			}
			if (ImGui::Button("VisualNormal"))
			{
				m_VisualNormal = !m_VisualNormal;
			}
			ImGui::Checkbox("MSAA On", &m_MSAAOn);
		}
	}
	void TestModel::ImportModel(const std::string& path)
	{
		m_Model = std::make_unique<Model>(path);
		m_Shader = std::make_unique<Shader>("Assimp");
		m_IsModelImported = true;
	}

	void TestModel::DrawSkybox()
	{
		if (m_Skybox)
		{
			m_Skybox->BindTexture(0);
			m_Skybox->Draw();
		}
	}
}