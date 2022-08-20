#include "Renderer.h"
#include<iostream>

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

struct Color
{
	float red, green, blue, alpha;
	Color(float r, float g, float b, float a) :red(r), green(g), blue(b), alpha(a) {};
};

const Color background = Color(0.2f, 0.3f, 0.3f, 1.0f);

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

void Renderer::Clear() const
{
	glClearColor(background.red, background.green, background.blue, background.alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
