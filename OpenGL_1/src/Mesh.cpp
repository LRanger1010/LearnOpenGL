#include "pch.h"
#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
	m_Vertices = vertices;
	m_Indices = indices;
	m_Textures = textures;
	SetMesh();
}

Mesh::~Mesh()
{

}

void Mesh::Draw(Shader& shader)
{
	unsigned int diffuseSlot = 0;
	unsigned int specularSlot = 0;
	unsigned int normalSlot = 0;
	for (unsigned int i = 0; i < m_Textures.size(); i++)
	{
		//glGenTextures(1, &m_Textures[0].id);
		shader.Bind();
		std::string name = "material." + m_Textures[i].type;
		if (m_Textures[i].type == "diffuse")
			name += std::to_string(diffuseSlot++);
		else if (m_Textures[i].type == "specular")
			name += std::to_string(specularSlot++);
		else if (m_Textures[i].type == "normal")
			name += std::to_string(normalSlot++);
		shader.SetUniform1i(name, i);
		shader.SetUniform3fv("material.ambient", m_Textures[i].matAmbient);
		shader.SetUniform3fv("material.diffuse", m_Textures[i].matDiffuse);
		shader.SetUniform3fv("material.specular", m_Textures[i].matSpecular);
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_Textures[i].id);
	}
	m_Renderer->Draw(*m_VAO, *m_IBO, shader);
}

void Mesh::SetMesh()
{
	m_VAO = std::make_unique<VertexArray>();
	m_VBO = std::make_unique<VertexBuffer>(&m_Vertices[0], m_Vertices.size() * sizeof(Vertex));
	m_IBO = std::make_unique<IndexBuffer>(&m_Indices[0], m_Indices.size());
	m_Renderer = std::make_unique<Renderer>();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoord));

}
