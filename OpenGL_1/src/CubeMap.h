#pragma once
#include "Renderer.h"

class CubeMap
{
public:
	CubeMap(GLint format, std::vector<std::string> paths);
	CubeMap(GLint format, unsigned int width, unsigned int height);
	~CubeMap();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	inline unsigned int GetRenderID() const { return m_RenderID; }
	inline int GetWith() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

private:
	unsigned int m_RenderID;
	int m_Width, m_Height, m_BytesPerPixel;
};