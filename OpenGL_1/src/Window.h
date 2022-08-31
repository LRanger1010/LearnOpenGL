#pragma once
#include "pch.h"

struct WindowProp
{
	unsigned int Width;
	unsigned int Height;
	std::string Name;
	WindowProp(unsigned int width = 800, unsigned int height = 600, const std::string& name = "Learn OpenGL")
		:Width(width), Height(height), Name(name) {};
};

class Window
{
public:
	virtual ~Window() {};

	virtual unsigned int GetWidth() = 0;
	virtual unsigned int GetHeight() = 0;
	virtual void OnUpdate() = 0;
	virtual void SetVSync(bool enabled) = 0;
	virtual bool IsVSync() = 0;

	static Window* Create(const WindowProp& prop = WindowProp());
};