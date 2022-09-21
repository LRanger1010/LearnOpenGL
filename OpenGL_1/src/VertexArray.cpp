#include "pch.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
	GLCALL(glGenVertexArrays(1, &m_RenderID));
	Bind();
}

VertexArray::~VertexArray()
{
	GLCALL(glDeleteVertexArrays(1, &m_RenderID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, unsigned int attribPointer/* = 0 */, unsigned int divisor/* = 0 */)
{
	Bind();
	vb.Bind();
	const auto& attribs = layout.GetAttribs();
	unsigned int stride = layout.GetStride();
	unsigned int offset = 0;
	for (unsigned int i = 0;i < attribs.size();i++)
	{
		const auto& attrib = attribs[i];
		GLCALL(glEnableVertexAttribArray(attribPointer + i));
		GLCALL(glVertexAttribPointer(attribPointer + i, attrib.count, attrib.type, attrib.normalized, stride, (const void*)offset));
		offset += attrib.count * VertexAttrib::GetSizeOfType(attrib.type);
		GLCALL(glVertexAttribDivisor(attribPointer + i, divisor));
	}
	
}

void VertexArray::Bind() const
{
	GLCALL(glBindVertexArray(m_RenderID));
}

void VertexArray::Unbind() const
{
	GLCALL(glBindVertexArray(0));
}
