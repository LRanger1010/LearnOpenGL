#include "pch.h"
#include "Cube.h"
#include "VertexBufferLayout.h"

static const unsigned int MaxQuadCount = 6;
static const unsigned int MaxVertexCount = 4 * MaxQuadCount;
static const unsigned int MaxIndexCount = 6 * MaxQuadCount;

//static const float vertices[] = {
//	//position			//normal		  //texture coord
//	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,	//0
//	0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,	//1
//	0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,	//2
//	-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,	//3
//
//	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	//4
//	0.5f, -0.5f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,	//5
//	0.5f, 0.5f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,	//6
//	0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,	//7
//
//	-0.5f, -0.5f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,	//8
//	0.5f, -0.5f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,	//9
//	0.5f, 0.5f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,	//10
//	-0.5f, 0.5f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,	//11
//
//	-0.5f, -0.5f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	//12
//	-0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,	//13
//	-0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,	//14
//	-0.5f, 0.5f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,	//15
//
//	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,	//16
//	0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	//17
//	0.5f, 0.5f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,	//18
//	-0.5f, 0.5f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,	//19
//
//	-0.5f, -0.5f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,	//20
//	0.5f, -0.5f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,	//21
//	0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,	//22
//	-0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,	//23
//};
#define DEFAULT_CUBE_TEXTURE_PATH "res/textures/container2.png"

Cube::Cube()
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
	m_Tex = std::make_unique<Image>(DEFAULT_CUBE_TEXTURE_PATH);*/
	SetMesh();
	SetMaterial();
}

Cube::~Cube()
{
}

void Cube::Update()
{
	
}

void Cube::Draw(Shader& shader)
{
	//m_Renderer.Draw(m_VAO, *m_IBO, shader);
	m_Material.SetShader(shader);
	m_Material.BindTextures();
	m_Renderer.Draw(*m_Mesh, m_Material);
}

void Cube::BindImage(unsigned int slot /*= 0*/)
{
	m_Material.BindTexture(slot);
}

void Cube::SetMesh()
{
	std::vector<Vertex> vertices;

	glm::vec2 uv1(0.0f, 0.0f);
	glm::vec2 uv2(1.0f, 0.0f);
	glm::vec2 uv3(1.0f, 1.0f);
	glm::vec2 uv4(0.0f, 1.0f);

	glm::vec3 pos1(-0.5f, -0.5f, 0.0f);
	glm::vec3 pos2(0.5f, -0.5f, 0.0f);
	glm::vec3 pos3(0.5f, 0.5f, 0.0f);
	glm::vec3 pos4(-0.5f, 0.5f, 0.0f);
	glm::vec3 normal(0.0f, 0.0f, 1.0f);
	SetFace(vertices, pos1, pos2, pos3, pos4, uv1, uv2, uv3, uv4, normal);
	
	pos1 = glm::vec3(0.5f, -0.5f, 0.0f);
	pos2 = glm::vec3(0.5f, -0.5f, -1.0f);
	pos3 = glm::vec3(0.5f, 0.5f, -1.0f);
	pos4 = glm::vec3(0.5f, 0.5f, 0.0f);
	normal = glm::vec3(1.0f, 0.0f, 0.0f);
	SetFace(vertices, pos1, pos2, pos3, pos4, uv1, uv2, uv3, uv4, normal);

	pos1 = glm::vec3(-0.5f, -0.5f, -1.0f);
	pos2 = glm::vec3(0.5f, -0.5f, -1.0f);
	pos3 = glm::vec3(0.5f, 0.5f, -1.0f);
	pos4 = glm::vec3(-0.5f, 0.5f, -1.0f);
	normal = glm::vec3(0.0f, 0.0f, -1.0f);
	SetFace(vertices, pos1, pos2, pos3, pos4, uv1, uv2, uv3, uv4, normal);

	pos1 = glm::vec3(-0.5f, -0.5f, -1.0f);
	pos2 = glm::vec3(-0.5f, -0.5f, 0.0f);
	pos3 = glm::vec3(-0.5f, 0.5f, 0.0f);
	pos4 = glm::vec3(-0.5f, 0.5f, -1.0f);
	normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	SetFace(vertices, pos1, pos2, pos3, pos4, uv1, uv2, uv3, uv4, normal);

	pos1 = glm::vec3(-0.5f, 0.5f, 0.0f);
	pos2 = glm::vec3(0.5f, 0.5f, 0.0f);
	pos3 = glm::vec3(0.5f, 0.5f, -1.0f);
	pos4 = glm::vec3(-0.5f, 0.5f, -1.0f);
	normal = glm::vec3(0.0f, 1.0f, 0.0f);
	SetFace(vertices, pos1, pos2, pos3, pos4, uv1, uv2, uv3, uv4, normal);

	pos1 = glm::vec3(-0.5f, -0.5f, -1.0f);
	pos2 = glm::vec3(0.5f, -0.5f, -1.0f);
	pos3 = glm::vec3(0.5f, -0.5f, 0.0f);
	pos4 = glm::vec3(-0.5f, -0.5f, 0.0f);
	normal = glm::vec3(0.0f, -1.0f, 0.0f);
	SetFace(vertices, pos1, pos2, pos3, pos4, uv1, uv2, uv3, uv4, normal);

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
	std::vector<unsigned int> indices(std::begin(indice), std::end(indice));
	m_Mesh = std::make_unique<Mesh>(vertices, indices);
}

void Cube::SetMaterial()
{
	std::vector<Texture> textures;
	Image img(DEFAULT_CUBE_TEXTURE_PATH);
	Texture texture;
	texture.id = img.GetRenderID();
	texture.type = "diffuse";
	textures.emplace_back(texture);

	m_Material.SetTexture(textures);
}

void Cube::SetFace(std::vector<Vertex> &vertices, glm::vec3 pos1, glm::vec3 pos2, glm::vec3 pos3, glm::vec3 pos4, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3, glm::vec2 uv4, glm::vec3 normal)
{
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
}
