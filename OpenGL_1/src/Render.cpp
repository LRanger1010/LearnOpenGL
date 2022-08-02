#include "Render.h"
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