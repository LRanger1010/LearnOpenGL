#include "pch.h"
#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout() :m_Stride(0)
{

}

VertexBufferLayout::~VertexBufferLayout()
{

}

void VertexBufferLayout::Push(unsigned int type, unsigned int count)
{
	unsigned char normalized = 0;
	switch (type)
	{
	case GL_FLOAT:
		normalized = GL_FALSE;
		break;
	case GL_UNSIGNED_INT:
		normalized = GL_FALSE;
		break;
	case GL_UNSIGNED_BYTE:
		normalized = GL_TRUE;
		break;
	}
	m_Attribs.push_back({ type, count, normalized });
	m_Stride += count * VertexAttrib::GetSizeOfType(type);
}

