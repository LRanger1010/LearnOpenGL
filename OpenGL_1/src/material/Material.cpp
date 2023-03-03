#include "pch.h"
#include "Material.h"

Material::Material(const std::string& name)
{
	SetShader(name);
}

Material::Material()
{

}

Material::~Material()
{

}

void Material::BindTextures() const
{
	/*if (!m_Shader)
		return;

	unsigned int diffuseSlot = 0;
	unsigned int specularSlot = 0;
	unsigned int normalSlot = 0;
	m_Shader->Bind();
	m_Shader->SetUniform3fv("material.ambient", m_Data.ambient);
	m_Shader->SetUniform3fv("material.diffuse", m_Data.diffuse);
	m_Shader->SetUniform3fv("material.specular", m_Data.specular);
	m_Shader->SetUniform1f("material.shininess", m_Data.shininess);*/
	for (unsigned int i = 0; i < m_Textures.size(); i++)
	{
		/*std::string name = "material." + m_Textures[i].type;
		if (m_Textures[i].type == "diffuse")
			name += std::to_string(diffuseSlot++);
		else if (m_Textures[i].type == "specular")
			name += std::to_string(specularSlot++);
		else if (m_Textures[i].type == "normal")
			name += std::to_string(normalSlot++);
		m_Shader->SetUniform1i(name, i);*/
		BindTexture(GL_TEXTURE_2D, m_Textures[i].GetRenderID(), i);
	}
}

void Material::BindTexture(unsigned int slot /*= 0*/) const
{
	BindTexture(GL_TEXTURE_2D, m_Textures[slot].GetRenderID(), slot);
}

void Material::BindTexture(GLenum target, unsigned int texId, unsigned int slot /*= 0*/) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(target, texId);
}

void Material::SetMaterialData(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	m_Data.ambient = ambient;
	m_Data.diffuse = diffuse;
	m_Data.specular = specular;
}

void Material::SetShader(const std::string& name)
{
	m_Shader = std::make_shared<Shader>(name);
}

void Material::SetShader(Shader& shader)
{
	if (m_Shader)
		m_Shader->Unbind();
	m_Shader = std::make_shared<Shader>(shader);
}

void Material::SetTextures(std::vector<Texture> textures)
{
	m_Textures = textures;
}

void Material::ResetTexture(Texture& tex, unsigned int slot)
{
	if (slot < m_Textures.size())
	{
		m_Textures[slot] = tex;
	}
}

void Material::Bind() const
{
	BindTextures();
	BindShader();
}

void Material::BindShader() const
{
	if (m_Shader)
	{
		m_Shader->Bind();
	}
}
