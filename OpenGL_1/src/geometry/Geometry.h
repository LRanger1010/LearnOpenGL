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
	virtual void SetMesh() = 0;
	virtual void Bind(unsigned int textureId, unsigned int slot = 0)
	{
		BindTexture(GL_TEXTURE_2D, textureId, slot);
	}
	virtual void BindImage(unsigned int slot = 0) {};

	void BindTexture(GLenum target, unsigned int textureId, unsigned int slot = 0)
	{
		GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
		GLCALL(glBindTexture(target, textureId));
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

protected:
	Renderer m_Renderer;
	VertexArray m_VAO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_IBO;
	glm::mat4 m_Model;
	std::vector<Mesh> m_Meshes;

private:

};