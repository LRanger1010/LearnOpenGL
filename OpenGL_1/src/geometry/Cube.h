#pragma once
#include "Geometry.h"

class Cube : public Geometry
{
public:
	Cube();
	~Cube();

	void Update() override;
	void Draw(Shader& shader) override;
	
protected:
	void SetMesh() override;
	void SetMaterial() override;

private:
	void SetFace(std::vector<Vertex>& vertices, glm::vec3 pos1, glm::vec3 pos2, glm::vec3 pos3, glm::vec3 pos4,
		glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3, glm::vec2 uv4, 
		glm::vec3 normal);
};