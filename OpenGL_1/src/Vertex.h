#pragma once
#include "glm/glm.hpp"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoord;
	float TexIndex;
	Vertex() {};
	Vertex(glm::vec3 pos, glm::vec2 texCoord, float index) :Position(pos), TexCoord(texCoord), TexIndex(index) {};
	~Vertex() {};
};