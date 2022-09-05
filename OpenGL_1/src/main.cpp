#include "pch.h"
#include "platform/WindowsWindow.h"

const unsigned int width = 1200;
const unsigned int height = 900;

int main()
{
	Window* window = Window::Create(WindowProp(width, height, "My Window"));
	window->OnUpdate();
	return 0;
}

