#include <glad/glad.h>
#include <glfw3.h>
#include<iostream>
#include<stdio.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "tests/TestMenu.h"
#include "camera/Camera.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int width = 800;
const unsigned int height = 600;

int main()
{
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfw window creation
	GLFWwindow * window = glfwCreateWindow(width, height, "Learn openGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to Create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSwapInterval(1);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
	
	{
		GLCALL(glEnable(GL_BLEND));
		GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCALL(glEnable(GL_DEPTH_TEST));

		CameraController cameraController(window);

		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();

		test::TestMenu testMenu;
		testMenu.RegisterTest<test::TestClearColor>("Clear Color");
		testMenu.RegisterTest<test::TestTexture2D>("2D Texture");
		testMenu.RegisterTest<test::TestBatchRenderingTexture2D>("Batch Rendering Texture");
		testMenu.RegisterTest<test::TestDynamicBatching>("Dynamic Batching");
		testMenu.RegisterTest<test::Test3DModel>("3D Model");
		testMenu.RegisterTest<test::TestPhoneShading>("Blinn-Phong Shading");
		testMenu.RegisterTest<test::TestMultiLights>("Multi-Lights");
		Renderer renderer;

		float deltaTime = 0;
		float lastFrame = 0;

		float clearColor[4] = { 0.1f,0.1f,0.1f,1.0f };

		// render loop
		while (!glfwWindowShouldClose(window))
		{
			float curFrame = (float)glfwGetTime();
			deltaTime = curFrame - lastFrame;
			lastFrame = curFrame;
			testMenu.OnUpdate(deltaTime);

			// camera update + input
			cameraController.Update(deltaTime);

			// render
			renderer.Clear(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
			testMenu.OnRender();

			// input
			//processInput(window);

			ImGui_ImplGlfwGL3_NewFrame();

			testMenu.OnGUI();
			ImGui::ColorEdit4("clear color", clearColor);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			glfwPollEvents();
			glfwSwapBuffers(window);
		}

		// optional: de-allocate all resources once they've outlived their purpose:

	}
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

