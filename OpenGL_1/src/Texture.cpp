#include "pch.h"
#include "Texture.h"

Texture::Texture(const std::string& path) : Texture(path, 4, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_TRUE, false)
{
	//stbi_set_flip_vertically_on_load(GL_TRUE);
	//m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BytesPerPixel, 4);

	//GLCALL(glGenTextures(1, &m_RenderID));
	//GLCALL(glBindTexture(GL_TEXTURE_2D, m_RenderID));

	////set the texture parameter, or it's going to black
	//GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	//GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	//GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	//GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	//GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	//Unbind();
}

Texture::Texture(const std::string& path, unsigned int req_channel, unsigned int min_filter_mode, unsigned int mag_filter_mode, unsigned int wrap_s_mode, unsigned int wrap_t_mode, bool fliped, bool generateMipmap)
	:m_RenderID(0), m_LocalBuffer(0), m_Width(0), m_Height(0), m_BytesPerPixel(0)
{
	stbi_set_flip_vertically_on_load(fliped);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BytesPerPixel, req_channel);

	GLCALL(glGenTextures(1, &m_RenderID));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_RenderID));

	//set the texture parameter, or it's going to black
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter_mode));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter_mode));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s_mode));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t_mode));

	GLenum format;
	if (m_BytesPerPixel == 1)
	{
		format = GL_RED;
	}
	else if (m_BytesPerPixel == 3)
	{
		format = GL_RGB;
	}
	else if (m_BytesPerPixel == 4)
	{
		format = GL_RGBA;
	}
	else
	{
		format = GL_RGBA8;
	}

	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_LocalBuffer));
	if(generateMipmap)
		GLCALL(glGenerateMipmap(GL_TEXTURE_2D));
	Unbind();
}

Texture::Texture(int width, int height, unsigned int min_filter_mode, unsigned int mag_filter_mode, unsigned int wrap_s_mode, unsigned int wrap_t_mode, unsigned int format)
	:m_RenderID(0), m_LocalBuffer(0), m_Width(width), m_Height(height), m_BytesPerPixel(0)
{
	GLCALL(glGenTextures(1, &m_RenderID));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_RenderID));

	//set the texture parameter, or it's going to black
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter_mode));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter_mode));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s_mode));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t_mode));
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr));
	Unbind();
}

Texture::~Texture()
{
	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
	GLCALL(glDeleteTextures(1, &m_RenderID));
}

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_RenderID));

	//glBindTextureUnit(GLuint slot, GLuint textureId); OpenGL 4.5 support
}

void Texture::Unbind() const
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::SetType(const std::string& type)
{
	m_Type = type;
}
