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
}

void ScreenMask::Update()
{
	m_Mask->Update();
}

void ScreenMask::BindTexture(unsigned int id, unsigned int slot /*= 0*/)
{
	m_Mask->Bind(id, slot);
}

void ScreenMask::Draw(unsigned int bindTexId, unsigned int bindSlot /*= 0*/)
{
	m_Shader->Bind();
	m_Shader->SetUniform1i("u_Texture", bindSlot);
	BindTexture(bindTexId, bindSlot);
	m_Mask->Draw(*m_Shader);
}
