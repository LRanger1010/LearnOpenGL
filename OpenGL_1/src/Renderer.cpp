#include "pch.h"
#include "Renderer.h"

void GLClearErrors()
{
	while (glGetError());
}

bool GLLogCall(const char* funcName, const char* fileName, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << funcName << " " << fileName << ":" << line << std::endl;
		return false;
	}
	return true;
}

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	va.Bind();
	ib.Bind();
	shader.Bind();
	GLCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0));
}

void Renderer::Draw(const VertexArray& va, const Shader& shader) const
{
	va.Bind();
	shader.Bind();
	GLCALL(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Renderer::DrawInstanced(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, unsigned int instanceCount) const
{
	va.Bind();
	ib.Bind();
	shader.Bind();
	GLCALL(glDrawElementsInstanced(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0, instanceCount));
}

void Renderer::Clear(float v0, float v1, float v2, float v3) const
{
	glClearColor(v0, v1, v2, v3);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
