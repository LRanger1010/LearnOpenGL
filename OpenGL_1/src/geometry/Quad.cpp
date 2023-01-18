#include "pch.h"
#include "Quad.h"
#include "VertexBufferLayout.h"

static const float vertices[] = {
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,	//0
	1.0f, -1.0f, 0.0f, 1.0f, 0.0f,	//1
	1.0f, 1.0f, 0.0f, 1.0f, 1.0f,	//2
	-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,	//3
};

unsigned int indice[] = {
	0, 1, 2,
	2, 3, 0,
};

#define DEFAULT_QUAD_TEXTURE_PATH "res/textures/wood.png"

Quad::Quad()
{
	/*m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
	{
		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 3);
		layout.Push(GL_FLOAT, 2);
		m_VAO.AddBuffer(*m_VBO, layout);
	}
	m_IBO = std::make_unique<IndexBuffer>(indice, 6);*/
	SetMesh();
	SetMaterial();
}

Quad::~Quad()
{

}

void Quad::Update()
{
	
}

void Quad::Draw(Shader& shader)
{
	//m_Renderer.Draw(m_VAO, *m_IBO, shader);
	m_Material.SetShader(shader);
	m_Material.BindTextures();
	m_Renderer.Draw(*m_Mesh, m_Material);
}

void Quad::SetMesh()
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	/*glm::vec3 matAmbient(0.0f);
	glm::vec3 matDiffuse(0.0f);
	glm::vec3 matSpecular(0.0f);*/

	glm::vec3 pos1(-1.0f, -1.0f, 0.0f);
	glm::vec3 pos2(1.0f, -1.0f, 0.0f);
	glm::vec3 pos3(1.0f, 1.0f, 0.0f);
	glm::vec3 pos4(-1.0f, 1.0f, 0.0f);

	glm::vec3 normal(0.0f, 0.0f, 1.0f);

	glm::vec2 uv1(0.0f, 0.0f);
	glm::vec2 uv2(1.0f, 0.0f);
	glm::vec2 uv3(1.0f, 1.0f);
	glm::vec2 uv4(0.0f, 1.0f);

	glm::vec3 tangent1 = CalcTangent(pos1, pos2, pos3, uv1, uv2, uv3);
	glm::vec3 tangent2 = CalcTangent(pos1, pos3, pos4, uv1, uv3, uv4);

	Vertex vertex1;
	vertex1.Position = pos1;
	vertex1.Normal = normal;
	vertex1.TexCoord = uv1;
	vertex1.Tangent = glm::normalize(tangent1 + tangent2);

	Vertex vertex2;
	vertex2.Position = pos2;
	vertex2.Normal = normal;
	vertex2.TexCoord = uv2;
	vertex2.Tangent = tangent1;

	Vertex vertex3;
	vertex3.Position = pos3;
	vertex3.Normal = normal;
	vertex3.TexCoord = uv3;
	vertex3.Tangent = glm::normalize(tangent1 + tangent2);

	Vertex vertex4;
	vertex4.Position = pos4;
	vertex4.Normal = normal;
	vertex4.TexCoord = uv4;
	vertex4.Tangent = tangent2;

	vertices.emplace_back(vertex1);
	vertices.emplace_back(vertex2);
	vertices.emplace_back(vertex3);
	vertices.emplace_back(vertex4);

	for (unsigned int i = 0; i < std::end(indice) - std::begin(indice); i++)
	{
		indices.emplace_back(indice[i]);
	}

	m_Mesh = std::make_unique<Mesh>(vertices, indices);
}

void Quad::SetMaterial()
{
	std::vector<Texture> textures;
	Image img(DEFAULT_QUAD_TEXTURE_PATH);
	Texture texture;
	texture.id = img.GetRenderID();
	texture.type = "diffuse";
	textures.emplace_back(texture);

	m_Material.SetTexture(textures);
}
