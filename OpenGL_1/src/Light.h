#pragma once
#include "glm/glm.hpp"

struct Light
{
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Light()
	{
		position = glm::vec3(1.2f, 1.0f, 2.0f);
		ambient = glm::vec3(0.2f, 0.2f, 0.2f);
		diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		specular = glm::vec3(1.0f, 1.0f, 1.0f);
	}
};