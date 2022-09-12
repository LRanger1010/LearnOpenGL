#include "pch.h"
#include "Test3DModel.h"

namespace test {

	static const std::string PostProcessList[6]{
		"screen",
		"Inversion",
		"Grayscale",
		"Sharpen",
		"Blur",
		"EdgeDetection",
	};

	Test3DModel::Test3DModel()
	{
		GLCALL(glEnable(GL_CULL_FACE));

		m_FBO = std::make_unique<FrameBuffer>(200, 150);
		m_FBO->AttachTextureColor(0);
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
			m_Quad->Update();
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
			m_Cube->BindTexture(0);
			m_Cube->Draw();

			GLCALL(glViewport(0, 0, 1200, 900));
			m_FBO->Unbind();
			GLCALL(glDisable(GL_DEPTH_TEST));
			GLCALL(glClear(GL_COLOR_BUFFER_BIT));
			unsigned int textureId = m_FBO->GetTextureColorBuffer();
			m_Quad->BindTexture(textureId, 0);
			m_Quad->Draw();
		}
	}

	void Test3DModel::OnGUI()
	{
		if (!m_Cube)
		{
			if (ImGui::Button("Cube"))
			{
				m_Cube = std::make_unique<Cube>();
				m_Quad = std::make_unique<Quad>();
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
					m_Quad->ResetShader(PostProcessList[i]);
				}
			}
			ImGui::Separator();
		}
	}

}