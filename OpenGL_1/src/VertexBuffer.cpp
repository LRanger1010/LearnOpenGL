#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	GLCALL(glGenBuffers(1, &m_RenderID));
}

VertexBuffer::~VertexBuffer()
{
	GLCALL(glDeleteBuffers(1, &m_RenderID));
}

void VertexBuffer::Bind(const void* data, unsigned int size) const
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::Unbind() const
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}