#pragma once
#include <vector>
#include "Renderer.h"

struct VertexAttrib
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return sizeof(GLfloat);
		case GL_UNSIGNED_INT:
			return sizeof(GLuint);
		case GL_UNSIGNED_BYTE:
			return sizeof(GLbyte);
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout();
	~VertexBufferLayout();

	/*template<typename T>
	void Push(int count)
	{
		static_assert(false);
	}
	template<>
	void Push<float>(unsigned int count)
	{
		m_Attribs.push_back({ GL_FLOAT, count, false });
		m_Stride += count * sizeof(float);
	}
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Attribs.push_back({ GL_UNSIGNED_INT, count, false });
		m_Stride += count * sizeof(unsigned int);
	}
	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Attribs.push_back({ GL_UNSIGNED_BYTE, count, true });
		m_Stride += count * sizeof(unsigned char);
	}*/

	void Push(unsigned int type, unsigned int count);

	inline unsigned int GetStride() const { return m_Stride; }
	inline const std::vector<VertexAttrib>& GetAttribs() const { return m_Attribs; }

private:
	std::vector<VertexAttrib> m_Attribs;
	unsigned int m_Stride;
};