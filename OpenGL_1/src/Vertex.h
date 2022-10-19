#pragma once

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoord;
	glm::vec3 Tangent;
	float TexIndex;
	Vertex() {};
	Vertex(glm::vec3 pos, glm::vec2 texCoord, float index) :Position(pos), TexCoord(texCoord), TexIndex(index) {};
	~Vertex() {};
};