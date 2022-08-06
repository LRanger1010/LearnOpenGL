#pragma once
#include<glad\glad.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCALL(x) GLClearErrors();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearErrors();

bool GLLogCall(const char* funcName, const char* fileName, int line);

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Draw(const VertexArray& va, const Shader& shader) const;
	void Clear() const;

private:

};