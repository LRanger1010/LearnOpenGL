#pragma once
#include "pch.h"
#include "Mesh.h"

class Model
{
public:
	Model(const std::string& path)
	{
		LoadModel(path);
	}
	~Model();

	void Draw(Shader& shader);
	void DrawInstanced(Shader& shader, unsigned int instanceCount);
	void BindVertexAttrib(const VertexBuffer& vb, const VertexBufferLayout& layout);

private:
	std::vector<std::unique_ptr<Mesh>> m_Meshes;
	std::string m_Directory;
	std::unordered_map<std::string, Texture> m_TextureLoaded;
private:
	void LoadModel(const std::string& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	std::unique_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
	unsigned int TextureFromFile(const std::string& path);
};