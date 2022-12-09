#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Mesh.h"
#include "Shader.h"
#include "material/Material.h"
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
	void Draw(const Mesh& mesh, const Material& mat) const;
	void DrawInstanced(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, unsigned int instanceCount) const;
	void DrawInstanced(const Mesh& mesh, const Material& mat, unsigned int instanceCount) const;
	void Clear(float v0, float v1, float v2, float v3) const;

private:

};