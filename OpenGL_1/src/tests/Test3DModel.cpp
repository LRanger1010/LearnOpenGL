#include "pch.h"
#include "Test3DModel.h"
#include "camera/Camera.h"

namespace test {

	static const std::string PostProcessList[6]{
		"screen",
		"Inversion",
		"Grayscale",
		"Sharpen",
		"Blur",
		"EdgeDetection",
	};

#define CUBE_SHADER "texture"

	Test3DModel::Test3DModel()
	{
		GLCALL(glEnable(GL_CULL_FACE));

		m_FBO = std::make_unique<FrameBuffer>(200, 150);
		m_ScreenTex = std::make_unique<Texture>(200, 150, GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_RGBA);
		m_FBO->AttachTextureColor(m_ScreenTex->GetRenderID(), 0);
		m_FBO->AttachRenderBuffer();
		m_FBO->Unbind();
	}

	Test3DModel::~Test3DModel()
	{
		GLCALL(glDisable(GL_CULL_FACE));
		GLCALL(glEnable(GL_DEPTH_TEST));
	}

	void Test3DModel::OnUpdate(float deltaTime)
	{
		if (m_Cube)
		{
			m_Cube->Update();
			m_ScreenMask->Update();
		}
	}

	void Test3DModel::OnRender()
	{
		if (m_Cube)
		{
			GLCALL(glViewport(0, 0, 200, 150));
			m_FBO->Bind();
			GLCALL(glEnable(GL_DEPTH_TEST));
			GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
			m_CubeShader->Bind();
			m_CubeShader->SetUniform1i("u_Texture", 0);
			m_CubeShader->SetUniformMat4f("u_MVP", MATRIX_VP * m_Cube->GetModelMatrix());
			//m_Cube->BindImage(0);
			m_Cube->Draw(*m_CubeShader);

			GLCALL(glViewport(0, 0, 1200, 900));
			m_FBO->Unbind();
			GLCALL(glDisable(GL_DEPTH_TEST));
			GLCALL(glClear(GL_COLOR_BUFFER_BIT));
			//unsigned int textureId = m_FBO->GetTextureColorBuffer();
			m_ScreenMask->Draw(*m_ScreenTex, 0);
		}
	}

	void Test3DModel::OnGUI()
	{
		if (!m_Cube)
		{
			if (ImGui::Button("Cube"))
			{
				m_Cube = std::make_unique<Cube>();
				m_Cube->Rotate(glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
				m_ScreenMask = std::make_unique<ScreenMask>();
				m_CubeShader = Shader::Find(CUBE_SHADER);
				m_Cube->GetMaterial().SetShader(*m_CubeShader);
			}
		}
		else
		{
			ImGui::Text("PostProcess");
			ImGui::Separator();
			for (int i = 0; i < (PostProcessList->end() - PostProcessList->begin()); i++)
			{
				if (ImGui::Button(PostProcessList[i].c_str()))
				{
					m_ScreenMask->SetShader(PostProcessList[i]);
				}
			}
			ImGui::Separator();
		}
	}

}