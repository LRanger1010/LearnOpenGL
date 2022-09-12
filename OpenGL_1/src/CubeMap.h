#pragma once
#include "Renderer.h"

class CubeMap
{
public:
	CubeMap(std::vector<std::string> paths);
	~CubeMap();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	inline int GetWith() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

private:
	unsigned int m_RenderID;
	int m_Width, m_Height, m_BytesPerPixel;
};