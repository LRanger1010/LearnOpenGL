#pragma once
#include "glm/glm.hpp"

struct Material
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
	unsigned int mainTex;
	unsigned int specTex;

	Material()
	{
		ambient = glm::vec3(1.0f, 0.5f, 0.3f);
		diffuse = glm::vec3(1.0f, 0.5f, 0.3f);
		specular = glm::vec3(0.5f, 0.5f, 0.5f);
		shininess = 32.0f;
		mainTex = 0;
		specTex = 1;
	}
};