#pragma once
#include "glm/glm.hpp"

struct Material
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

	Material()
	{
		ambient = glm::vec3(1.0f, 0.5f, 0.3f);
		diffuse = glm::vec3(1.0f, 0.5f, 0.3f);
		specular = glm::vec3(0.5f, 0.5f, 0.5f);
		shininess = 32.0f;
	}
};