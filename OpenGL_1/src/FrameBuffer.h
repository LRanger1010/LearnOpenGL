#pragma once
#include "pch.h"
#include "Renderer.h"

class FrameBuffer
{
public:
	FrameBuffer(unsigned int width, unsigned int height);
	~FrameBuffer();

	inline unsigned int GetTextureColorBuffer() const { return m_TextureColorBuffer; }
	void Bind() const;
	void Unbind() const;
	void AttachTextureColor(unsigned int slot);
	void AttachTextureDepth();
	void AttachTextureStencil();
	void AttachTextureDepthStencil();
	void AttachRenderBuffer();

private:
	unsigned int m_RenderID;
	unsigned int m_Width, m_Height;
	unsigned int m_TextureColorBuffer;
	unsigned int m_TextureDepthBuffer;
	unsigned int m_TextureStencilBuffer;
	unsigned int m_TextureDepthStencilBuffer;
	unsigned int m_RBO;
};