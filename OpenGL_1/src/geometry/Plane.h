#pragma once
#include "Renderer.h"
#include "Image.h"

class Plane
{
public:
	Plane();
	~Plane();

	inline Shader& GetShader() const { return *m_Shader; }
	inline glm::mat4 GetModelMatrix() const { return m_Model; }
	void Update();
	void Draw();
	void BindTexture(unsigned int slot = 0);
	void BindTexture(unsigned int textureId, unsigned int slot);
	void ResetShader(std::shared_ptr<Shader> shader_ptr);

private:
	Renderer m_Renderer;
	VertexArray m_VAO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_IBO;
	std::shared_ptr<Shader> m_Shader;
	std::unique_ptr<Image> m_Tex;
	glm::mat4 m_MVP;
	glm::mat4 m_Model;
};