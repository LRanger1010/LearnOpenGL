#include "pch.h"
#include "Model.h"

Model::~Model()
{

}

void Model::Draw(Shader& shader)
{
	for (int i = 0; i < m_Meshes.size(); i++)
	{
		m_Meshes[i].Draw(shader);
	}
}

void Model::LoadModel(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags | AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "error:" << importer.GetErrorString() << std::endl;
		return;
	}
	m_Directory = path.substr(0, path.find_last_of('/'));
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		auto mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.push_back(ProcessMesh(mesh, scene));
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 pos(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		glm::vec3 norm(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		glm::vec2 texCoord;
		if (mesh->mTextureCoords[0])
		{
			texCoord.x = mesh->mTextureCoords[0][i].x;
			texCoord.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			texCoord.x = 0.0f;
			texCoord.y = 0.0f;
		}
		vertex.Position = pos;
		vertex.Normal = norm;
		vertex.TexCoord = texCoord;
		vertices.push_back(vertex);

		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			auto face = mesh->mFaces[i];
			for (int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		if (mesh->mMaterialIndex > 0)
		{
			auto mat = scene->mMaterials[mesh->mMaterialIndex];
			auto diffuseList = LoadMaterialTextures(mat, aiTextureType_DIFFUSE, "diffuse");
			textures.insert(textures.end(), diffuseList.begin(), diffuseList.end());
			auto specularList = LoadMaterialTextures(mat, aiTextureType_SPECULAR, "specular");
			textures.insert(textures.end(), specularList.begin(), specularList.end());
		}
	}
	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
{
	std::vector<Texture> textures;
	for (int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		std::string path = m_Directory + '/' + std::string(str.C_Str());
		if (m_TextureLoaded.find(path) != m_TextureLoaded.end())
		{
			textures.push_back(m_TextureLoaded[path]);
		}
		else
		{
			Texture texture;
			texture.id = TextureFromFile(path);
			texture.type = typeName;
			textures.push_back(texture);
			m_TextureLoaded[path] = texture;
		}
	}
	return textures;
}

unsigned int Model::TextureFromFile(const std::string& path)
{
	unsigned int id;
	stbi_set_flip_vertically_on_load(1);
	int width, height, bpp;
	auto localBuffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);

	GLCALL(glGenTextures(1, &id));
	GLCALL(glBindTexture(GL_TEXTURE_2D, id));

	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCALL((GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

	return id;
}
