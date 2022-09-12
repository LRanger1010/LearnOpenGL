#include "pch.h"
#include "FrameBuffer.h"

static const GLenum AttachmentEnum[] = {
	GL_COLOR_ATTACHMENT0,
	GL_COLOR_ATTACHMENT1,
	GL_COLOR_ATTACHMENT2,
	GL_COLOR_ATTACHMENT3,
	//...
};

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
	:m_Width(width), m_Height(height)
{
	GLCALL(glGenFramebuffers(1, &m_RenderID));
	Bind();
}

FrameBuffer::~FrameBuffer()
{
	GLCALL(glDeleteFramebuffers(1, &m_RenderID));
}

void FrameBuffer::Bind() const
{
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, m_RenderID));
}

void FrameBuffer::Unbind() const
{
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Error: FrameBuffer is not complete!" << std::endl;
	}
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void FrameBuffer::AttachTextureColor(unsigned int slot)
{
	GLCALL(glGenTextures(1, &m_TextureColorBuffer));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_TextureColorBuffer));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
	GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, AttachmentEnum[slot], GL_TEXTURE_2D, m_TextureColorBuffer, 0));
}

void FrameBuffer::AttachTextureDepth()
{
	GLCALL(glGenTextures(1, &m_TextureDepthBuffer));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_TextureDepthBuffer));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_Width, m_Height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr));
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
	GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_TextureDepthBuffer, 0));
}

void FrameBuffer::AttachTextureStencil()
{
	GLCALL(glGenTextures(1, &m_TextureStencilBuffer));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_TextureStencilBuffer));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_INDEX, m_Width, m_Height, 0, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, nullptr));
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
	GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_TextureStencilBuffer, 0));
}

void FrameBuffer::AttachTextureDepthStencil()
{
	GLCALL(glGenTextures(1, &m_TextureDepthStencilBuffer));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_TextureDepthStencilBuffer));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Width, m_Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr));
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
	GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_TextureDepthStencilBuffer, 0));
}

void FrameBuffer::AttachRenderBuffer()
{
	GLCALL(glGenRenderbuffers(1, &m_RBO));
	GLCALL(glBindRenderbuffer(GL_RENDERBUFFER, m_RBO));
	GLCALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height));
	GLCALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO));
}
