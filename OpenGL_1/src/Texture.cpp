#include "Texture.h"

Texture::Texture(const std::string& path)
	:m_RenderID(0), m_LocalBuffer(0), m_Width(0), m_Height(0), m_BytesPerPixel(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BytesPerPixel, 4);

	GLCALL(glGenTextures(1, &m_RenderID));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_RenderID));

	//set the texture parameter, or it's going to black
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
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