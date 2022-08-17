#pragma once

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer(unsigned int size);
	~VertexBuffer();
	void Bind() const;
	void Bind(const void* data, unsigned int size) const;
	void Unbind() const;

private:
	unsigned int m_RenderID;
};