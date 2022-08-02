#pragma once
#include<glad\glad.h>
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCALL(x) GLClearErrors();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearErrors();

bool GLLogCall(const char* funcName, const char* fileName, int line);