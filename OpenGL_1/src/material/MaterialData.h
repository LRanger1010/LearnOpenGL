#pragma once

struct MaterialData
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
	int mainTex;
	int specTex;

	MaterialData()
	{
		ambient = glm::vec3(1.0f, 1.0f, 1.0f);
		diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
		specular = glm::vec3(1.0f, 1.0f, 1.0f);
		shininess = 32.0f;
		mainTex = 0;
		specTex = 1;
	}
};