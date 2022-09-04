#pragma once
#include "Renderer.h"

class Image
{
public:
	//Image();
	Image(const std::string& path);
	~Image();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
	inline int GetWith() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

private:
	unsigned int m_RenderID;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BytesPerPixel;

};