#pragma once
#include "pch.h"

struct Texture
{
	unsigned int id;
	std::string type;
	glm::vec3 matAmbient;
	glm::vec3 matDiffuse;
	glm::vec3 matSpecular;
};