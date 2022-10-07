#include "pch.h"
#include "CubeMap.h"

CubeMap::CubeMap(std::vector<std::string> paths)
	:m_RenderID(0), m_Width(0), m_Height(0), m_BytesPerPixel(0)
{
	stbi_set_flip_vertically_on_load(GL_FALSE);
	GLCALL(glGenTextures(1, &m_RenderID));
	GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RenderID));

	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

	unsigned char* buffer = nullptr;
	for (int i = 0; i < paths.size(); i++)
	{
		buffer = stbi_load(paths[i].c_str(), &m_Width, &m_Height, &m_BytesPerPixel, 0);
		GLCALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer));
		stbi_image_free(buffer);
	}
	buffer = nullptr;
	Unbind();
}

CubeMap::~CubeMap()
{
	GLCALL(glDeleteTextures(1, &m_RenderID));
}

void CubeMap::Bind(unsigned int slot /*= 0*/) const
{
	GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
	GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RenderID));
}

void CubeMap::Unbind() const
{
	GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}
