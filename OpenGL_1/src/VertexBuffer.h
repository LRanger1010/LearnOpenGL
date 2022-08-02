#pragma once
#include "Render.h"

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();
	void Bind(const void* data, unsigned int size) const;
	void Unbind() const;

private:
	unsigned int m_RenderID;
};