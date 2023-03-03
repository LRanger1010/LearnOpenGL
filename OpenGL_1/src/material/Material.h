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
	inline glm::vec3 GetAmbient() const { return m_Data.ambient; }
	inline glm::vec3 GetDiffuse() const { return m_Data.diffuse; }
	inline glm::vec3 GetSpecular() const { return m_Data.specular; }
	inline float GetShininess() const { return m_Data.shininess; }

	void SetMaterialData(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	void SetShader(const std::string& name);
	void SetShader(Shader& shader);
	void SetTextures(std::vector<Texture> textures);
	void ResetTexture(Texture& tex, unsigned int slot);
	void Bind() const;
	void BindTextures() const;
	void BindTexture(unsigned int slot = 0) const;
	void BindTexture(GLenum target, unsigned int texId, unsigned int slot = 0) const;
	void BindShader() const;

private:
	std::shared_ptr<Shader> m_Shader;
	std::vector<Texture> m_Textures;
	MaterialData m_Data;
};