#include "pch.h"
#include "Model.h"

Model::~Model()
{

}

void Model::Draw(Shader& shader)
{
	for (unsigned int i = 0; i < m_Meshes.size(); i++)
	{
		m_Meshes[i]->Draw(shader);
	}
}

void Model::LoadModel(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "error:" << importer.GetErrorString() << std::endl;
		return;
	}
	m_Directory = path.substr(0, path.find_last_of('/'));
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		auto mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.push_back(ProcessMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

std::unique_ptr<Mesh> Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 pos(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		glm::vec3 norm;
		if (mesh->HasNormals())
		{
			norm.x = mesh->mNormals[i].x;
			norm.y = mesh->mNormals[i].y;
			norm.z = mesh->mNormals[i].z;
		}
		else
		{
			norm.x = 0.0f;
			norm.y = 0.0f;
			norm.z = 0.0f;
		}
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
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		auto face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
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
		auto normalList = LoadMaterialTextures(mat, aiTextureType_HEIGHT, "normal");
		textures.insert(textures.end(), normalList.begin(), normalList.end());
	}
	return std::make_unique<Mesh>(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
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
	int width, height, bpp;
	auto localBuffer = stbi_load(path.c_str(), &width, &height, &bpp, 0);

	GLCALL(glGenTextures(1, &id));
	GLCALL(glBindTexture(GL_TEXTURE_2D, id));

	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	GLenum format;
	if (bpp == 1)
	{
		format = GL_RED;
	}
	else if (bpp == 3)
	{
		format = GL_RGB;
	}
	else if (bpp == 4)
	{
		format = GL_RGBA;
	}
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, localBuffer));
	GLCALL(glGenerateMipmap(GL_TEXTURE_2D));
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

	stbi_image_free(localBuffer);

	return id;
}
