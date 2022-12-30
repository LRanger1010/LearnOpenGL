#pragma once
#include "MaterialData.h"
#include "Texture.h"
#include "Shader.h"

class Material
{
public:
	Material(const std::string& name);
	Material();
	~Material();
	inline std::shared_ptr<Shader> GetShader() const { return m_Shader; }
	inline std::vector<Texture> GetTextures() const { return m_Textures; }

	void SetMaterialData(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	void SetShader(const std::string& name);
	void SetShader(Shader& shader);
	void SetTexture(std::vector<Texture> textures);
	void BindTextures();
	void BindTexture(unsigned int slot = 0);
	void BindShader() const;

private:
	std::shared_ptr<Shader> m_Shader;
	std::vector<Texture> m_Textures;
	MaterialData m_Data;
};