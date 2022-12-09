#include "pch.h"
#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	m_Vertices = vertices;
	m_Indices = indices;
	/*m_Textures = textures;
	m_MatAmbient = matAmbient;
	m_MatDiffuse = matDiffuse;
	m_MatSpecular = matSpecular;
	m_Shininess = 32.0f;*/
	m_AttribPointer = 0;
	SetMesh();
}

Mesh::~Mesh()
{

}

//void Mesh::Draw(Shader& shader)
//{
//	//BindTextures(shader);
//	//m_Renderer->Draw(*m_VAO, *m_IBO, shader);
//}

//void Mesh::DrawInstanced(Shader& shader, unsigned int instanceCount)
//{
//	//BindTextures(shader);
//	//m_Renderer->DrawInstanced(*m_VAO, *m_IBO, shader, instanceCount);
//}

void Mesh::AddVertexAttrib(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	m_VAO->AddBuffer(vb, layout, m_AttribPointer++, 1);
}

void Mesh::SetMesh()
{
	m_VAO = std::make_unique<VertexArray>();
	m_VBO = std::make_unique<VertexBuffer>(&m_Vertices[0], m_Vertices.size() * sizeof(Vertex));
	m_IBO = std::make_unique<IndexBuffer>(&m_Indices[0], m_Indices.size());
	//m_Renderer = std::make_unique<Renderer>();
	glEnableVertexAttribArray(m_AttribPointer);
	glVertexAttribPointer(m_AttribPointer++, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));

	glEnableVertexAttribArray(m_AttribPointer);
	glVertexAttribPointer(m_AttribPointer++, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(m_AttribPointer);
	glVertexAttribPointer(m_AttribPointer++, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoord));

	glEnableVertexAttribArray(m_AttribPointer);
	glVertexAttribPointer(m_AttribPointer++, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Tangent));
}

//void Mesh::BindTextures(Shader& shader)
//{
//	/*unsigned int diffuseSlot = 0;
//	unsigned int specularSlot = 0;
//	unsigned int normalSlot = 0;
//	shader.Bind();
//	shader.SetUniform3fv("material.ambient", m_MatAmbient);
//	shader.SetUniform3fv("material.diffuse", m_MatDiffuse);
//	shader.SetUniform3fv("material.specular", m_MatSpecular);
//	shader.SetUniform1f("material.shininess", m_Shininess);
//	for (unsigned int i = 0; i < m_Textures.size(); i++)
//	{
//		std::string name = "material." + m_Textures[i].type;
//		if (m_Textures[i].type == "diffuse")
//			name += std::to_string(diffuseSlot++);
//		else if (m_Textures[i].type == "specular")
//			name += std::to_string(specularSlot++);
//		else if (m_Textures[i].type == "normal")
//			name += std::to_string(normalSlot++);
//		shader.SetUniform1i(name, i);
//		glActiveTexture(GL_TEXTURE0 + i);
//		glBindTexture(GL_TEXTURE_2D, m_Textures[i].id);
//	}*/
//}

void Mesh::Bind() const
{
	m_VAO->Bind();
	m_IBO->Bind();
}
