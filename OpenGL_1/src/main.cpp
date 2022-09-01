#include "pch.h"
#include "platform/WindowsWindow.h"

const unsigned int width = 800;
const unsigned int height = 600;

int main()
{
	Window* window = Window::Create(WindowProp(width, height, "My Window"));
	window->OnUpdate();
	return 0;
}

