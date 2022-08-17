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

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& attribs = layout.GetAttribs();
	unsigned int stride = layout.GetStride();
	unsigned int offset = 0;
	for (unsigned int i = 0;i < attribs.size();i++)
	{
		const auto& attrib = attribs[i];
		GLCALL(glEnableVertexAttribArray(i));
		GLCALL(glVertexAttribPointer(i, attrib.count, attrib.type, attrib.normalized, stride, (const void*)offset));
		offset += attrib.count * VertexAttrib::GetSizeOfType(attrib.type);
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
