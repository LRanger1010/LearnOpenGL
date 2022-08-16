#pragma once
#include "glm/glm.hpp"

struct vec3
{
	float x, y, z;
};

struct vec2
{
	float x, y;
};

struct Vertex
{
	vec3 Position;
	vec2 TexCoord;
	float TexIndex;
	Vertex() {};
	Vertex(vec3 pos, vec2 texCoord, float index) :Position(pos), TexCoord(texCoord), TexIndex(index) {};
	~Vertex() {};
};