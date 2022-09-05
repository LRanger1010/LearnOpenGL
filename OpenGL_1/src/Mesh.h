#pragma once
#include "pch.h"
#include "Vertex.h"
#include "Renderer.h"
#include "Texture.h"

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	~Mesh();

	inline std::vector<Vertex> GetVertices() const { return m_Vertices; }
	inline std::vector<unsigned int> GetIndices() const { return m_Indices; }
	inline std::vector<Texture> GetTextures() const { return m_Textures; }
	void Draw(Shader& shader);

private:
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<Texture> m_Textures;
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_IBO;
	std::unique_ptr<Renderer> m_Renderer;
private:
	void SetMesh();
};