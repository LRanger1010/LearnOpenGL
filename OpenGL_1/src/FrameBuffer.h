#pragma once
#include "pch.h"
#include "Renderer.h"

class FrameBuffer
{
public:
	FrameBuffer(unsigned int width, unsigned int height);
	~FrameBuffer();

	inline unsigned int GetTextureColorBuffer() const { return m_TextureColorBuffer; }
	inline unsigned int GetTextureDepthBuffer() const { return m_TextureDepthBuffer; }
	inline unsigned int GetWidth() const { return m_Width; }
	inline unsigned int GetHeight() const { return m_Height; }
	inline unsigned int GetID() const { return m_RenderID; }
	void Bind(GLenum target = GL_FRAMEBUFFER) const;
	void Unbind(GLenum target = GL_FRAMEBUFFER) const;
	void CreateTextureDepth();
	void AttachTextureColor(unsigned int texId, unsigned int slot);
	void AttachMultiSampleTextureColor(unsigned int slot, unsigned int samples);
	void AttachTextureDepth();
	void AttachCubeMapDepth(unsigned int cubeMapDepthBuffer);
	void AttachTextureStencil();
	void AttachTextureDepthStencil();
	void AttachRenderBuffer();
	void AttachMultiSampleRenderBuffer(unsigned int samples);
	void SetBufferTarget(GLenum buffer);

	static void BlitFramebuffer(const FrameBuffer& src, const FrameBuffer& dst);
	static void BlitFramebuffer(const FrameBuffer& src);

private:
	unsigned int m_RenderID;
	unsigned int m_Width, m_Height;
	unsigned int m_TextureColorBuffer;
	unsigned int m_TextureDepthBuffer;
	unsigned int m_TextureStencilBuffer;
	unsigned int m_TextureDepthStencilBuffer;
	unsigned int m_RBO;
};