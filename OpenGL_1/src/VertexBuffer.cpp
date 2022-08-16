#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCALL(glGenBuffers(1, &m_RenderID));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(unsigned int size)
{
	GLCALL(glGenBuffers(1, &m_RenderID));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCALL(glDeleteBuffers(1, &m_RenderID));
}

void VertexBuffer::Bind() const
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
}

void VertexBuffer::Bind(const void* data) const
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
	GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(data), data));
}

void VertexBuffer::Unbind() const
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}