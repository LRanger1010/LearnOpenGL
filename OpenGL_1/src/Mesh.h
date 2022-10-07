#pragma once
#include "Vertex.h"
#include "Renderer.h"
#include "Texture.h"

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, glm::vec3 matAmbient, glm::vec3 matDiffuse, glm::vec3 matSpecular);
	~Mesh();

	inline std::vector<Vertex> GetVertices() const { return m_Vertices; }
	inline std::vector<unsigned int> GetIndices() const { return m_Indices; }
	inline std::vector<Texture> GetTextures() const { return m_Textures; }
	void Draw(Shader& shader);
	void DrawInstanced(Shader& shader, unsigned int instanceCount);
	void AddVertexAttrib(const VertexBuffer& vb, const VertexBufferLayout& layout);

private:
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<Texture> m_Textures;
	glm::vec3 m_MatAmbient;
	glm::vec3 m_MatDiffuse;
	glm::vec3 m_MatSpecular;
	float m_Shininess;
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_IBO;
	std::unique_ptr<Renderer> m_Renderer;
	unsigned int m_AttribPointer;
private:
	void SetMesh();
	void BindTextures(Shader& shader);
};