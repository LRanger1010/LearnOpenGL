#include "pch.h"
#include "ScreenMask.h"

ScreenMask::ScreenMask()
{
	m_Mask = std::make_unique<Quad>();
	SetShader(DEFAULT_SCREEN_SHADER);
}

ScreenMask::~ScreenMask()
{

}

void ScreenMask::SetShader(const std::string& name)
{
	m_Shader = Shader::Find(name);
	if (m_Mask)
	{
		m_Mask->GetMaterial().SetShader(*m_Shader);
	}
}

void ScreenMask::Update()
{
	m_Mask->Update();
}

//void ScreenMask::BindTexture(unsigned int id, unsigned int slot /*= 0*/)
//{
//	m_Mask->BindTexture(id, slot);
//}

void ScreenMask::Draw(Texture& bindTex, unsigned int bindSlot /*= 0*/)
{
	m_Shader->Bind();
	m_Shader->SetUniform1i("u_Texture", bindSlot);
	//BindTexture(bindTexId, bindSlot);
	m_Mask->ResetTexture(bindTex, bindSlot);
	m_Mask->Draw(*m_Shader);
}
