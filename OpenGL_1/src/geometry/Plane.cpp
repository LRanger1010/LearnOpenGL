#include "pch.h"
#include "Plane.h"
#include "VertexBufferLayout.h"

static const unsigned int MaxIndexCount = 6;

static const float vertices[] = {
	// positions            // normals         // texcoords
		-2.0f, -0.5f,  2.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
		2.0f, -0.5f,  2.0f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
		2.0f, -0.5f, -2.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
	   -2.0f, -0.5f, -2.0f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
};

#define DEFAULT_PLANE_TEXTURE_PATH "res/textures/wood.png"

Plane::Plane()
{
	/*m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
	{
		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 3);
		layout.Push(GL_FLOAT, 3);
		layout.Push(GL_FLOAT, 2);
		m_VAO.AddBuffer(*m_VBO, layout);
	}

	unsigned int indice[MaxIndexCount];
	unsigned int offset = 0;
	for (int i = 0; i < MaxIndexCount; i += 6)
	{
		indice[i] = offset;
		indice[i + 1] = offset + 1;
		indice[i + 2] = offset + 2;
		indice[i + 3] = offset + 2;
		indice[i + 4] = offset + 3;
		indice[i + 5] = offset;

		offset += 4;
	}

	m_IBO = std::make_unique<IndexBuffer>(indice, MaxIndexCount);
	m_Tex = std::make_unique<Image>(DEFAULT_PLANE_TEXTURE_PATH);*/
	SetMesh();
	SetMaterial();
}

Plane::~Plane()
{
}

void Plane::Update()
{
}

void Plane::Draw(Shader& shader)
{
	//m_Renderer.Draw(m_VAO, *m_IBO, shader);
	m_Material.SetShader(shader);
	m_Material.BindTextures();
	m_Renderer.Draw(*m_Mesh, m_Material);
}

//void Plane::BindTexture(unsigned int slot /*= 0*/)
//{
//	//m_Tex->Bind(slot);
//	m_Material.BindTexture(slot);
//}

void Plane::SetMesh()
{
	std::vector<Vertex> vertices;

	glm::vec3 pos1(-2.0f, -0.5f, 2.0f);
	glm::vec3 pos2(2.0f, -0.5f, 2.0f);
	glm::vec3 pos3(2.0f, -0.5f, -2.0f);
	glm::vec3 pos4(-2.0f, -0.5f, -2.0f);

	glm::vec3 normal(0.0f, 1.0f, 0.0f);

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

	unsigned int offset = 0;
	unsigned int indices[MaxIndexCount];
	for (int i = 0; i < MaxIndexCount; i += 6)
	{
		indices[i] = offset;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;
		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset;

		offset += 4;
	}
	std::vector<unsigned int> indice(std::begin(indices), std::end(indices));
	m_Mesh = std::make_unique<Mesh>(vertices, indice);
}

void Plane::SetMaterial()
{
	std::vector<Texture> textures;
	Texture img(DEFAULT_PLANE_TEXTURE_PATH);
	Texture texture;
	texture.id = img.GetRenderID();
	texture.type = "diffuse";
	textures.emplace_back(texture);

	m_Material.SetTextures(textures);
}
