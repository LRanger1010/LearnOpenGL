#pragma once
#include "pch.h"
#include "Mesh.h"
#include "material/Material.h"
#include "Renderer.h"

class Model
{
public:
	Model(const std::string& path)
	{
		LoadModel(path);
		m_Renderer = std::make_unique<Renderer>();
	}
	~Model();

	inline std::vector<Material> GetMaterials() const { return m_Materials; }
	void Draw(Shader& shader);
	void DrawInstanced(Shader& shader, unsigned int instanceCount);
	void BindVertexAttrib(const VertexBuffer& vb, const VertexBufferLayout& layout);

private:
	std::vector<std::unique_ptr<Mesh>> m_Meshes;
	std::vector<Material> m_Materials;
	std::unique_ptr<Renderer> m_Renderer;
	std::string m_Directory;
	std::unordered_map<std::string, Texture> m_TextureLoaded;
private:
	void LoadModel(const std::string& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	std::unique_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
	unsigned int TextureFromFile(const std::string& path);
};