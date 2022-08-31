#include "pch.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "tests/TestMenu.h"
#include "camera/Camera.h"
#include "platform/WindowsWindow.h"

//void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int width = 800;
const unsigned int height = 600;

int main()
{
	Window* window = Window::Create(WindowProp(width, height, "My Window"));
	window->OnUpdate();

	//	CameraController cameraController(window);

	//		// camera update + input
	//		cameraController.Update(deltaTime);

	//		// input
	//		//processInput(window);
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

