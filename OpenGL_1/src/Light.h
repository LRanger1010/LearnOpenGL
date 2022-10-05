#pragma once

struct Light
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Light()
	{
		ambient = glm::vec3(0.2f, 0.2f, 0.2f);
		diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		specular = glm::vec3(1.0f, 1.0f, 1.0f);
	}
};

struct DirLight : Light
{
	glm::vec3 direction;
	glm::mat4 view;
	DirLight()
	{
		direction = glm::vec3(-0.2f, -1.0f, -0.3f);
		view = glm::lookAt(-direction, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}
};

struct PointLight : Light
{
	glm::vec3 position;
	float constant;
	float linear;
	float quadratic;
	PointLight()
	{
		position = glm::vec3(1.2f, 1.0f, 2.0f);
		constant = 1.0f;
		linear = 0.09f;
		quadratic = 0.032f;
	}
};

struct SpotLight : Light
{
	glm::vec3 position;
	glm::vec3 direction;
	float cutOff;
	float outterCutOff;
	SpotLight()
	{
		diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
		position = glm::vec3(0.0f, 0.0f, 0.0f);
		direction = glm::vec3(0.0f, 0.0f, -1.0f);
		cutOff = glm::cos(glm::radians(5.0f));
		outterCutOff = glm::cos(glm::radians(10.0f));
	}
};