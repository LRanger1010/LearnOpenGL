#include "VertexArray.h"
#include "Render.h"


VertexArray::VertexArray()
{
	GLCALL(glGenVertexArrays(1, &m_RenderID));
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
	for (unsigned int i = 0;i < attribs.size();i++)
	{
		const auto& attrib = attribs[i];
		GLCALL(glEnableVertexAttribArray(i));
		GLCALL(glVertexAttribPointer(i, attrib.count, attrib.type, attrib.normalized, stride, (const void*)(i * attrib.count * VertexAttrib::GetSizeOfType(attrib.type))));
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
