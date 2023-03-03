#pragma once
#include "pch.h"
#include "Renderer.h"
#include "Mesh.h"

class Geometry
{
public:
	Geometry()
		:m_Model(glm::mat4(1.0f)) 
	{};
	virtual ~Geometry() {};
	inline glm::mat4 GetModelMatrix() const { return m_Model; }
	virtual void Update() = 0;
	virtual void Draw(Shader& shader) = 0;
	void BindTexture(unsigned int slot)
	{
		m_Material.BindTexture(slot);
	}
	void BindTexture(unsigned int textureId, unsigned int slot)
	{
		BindTexture(GL_TEXTURE_2D, textureId, slot);
	}
	void BindTexture(GLenum target, unsigned int textureId, unsigned int slot)
	{
		m_Material.BindTexture(target, textureId, slot);
	}
	void ResetTexture(Texture& tex, unsigned int slot)
	{
		m_Material.ResetTexture(tex, slot);
	}
	void Translate(glm::vec3 vec)
	{
		m_Model = glm::translate(m_Model, vec);
	}
	void Rotate(float angle, glm::vec3 axis)
	{
		m_Model = glm::rotate(m_Model, angle, axis);
	}
	void Scale(glm::vec3 vec)
	{
		m_Model = glm::scale(m_Model, vec);
	}

	Material& GetMaterial() { return m_Material; }

protected:
	Renderer m_Renderer;
	VertexArray m_VAO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_IBO;
	glm::mat4 m_Model;
	std::unique_ptr<Mesh> m_Mesh;
	Material m_Material;

protected:
	virtual void SetMesh() = 0;
	virtual void SetMaterial() = 0;
	glm::vec3 CalcTangent(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 pos3, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3)
	{
		glm::vec3 edge1 = pos2 - pos1;
		glm::vec3 edge2 = pos3 - pos1;
		glm::vec2 deltaUV1 = uv2 - uv1;
		glm::vec2 deltaUV2 = uv3 - uv1;

		float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		glm::vec3 tangent;
		tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
		return glm::normalize(tangent);
	}

private:
	
};