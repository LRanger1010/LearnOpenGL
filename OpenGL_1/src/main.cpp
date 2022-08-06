#include<glad\glad.h>
#include<glfw3.h>
#include<iostream>
#include<stdio.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int width = 800;
const unsigned int height = 600;

//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"layout (location = 1) in vec3 aColor;\n"
//"out vec3 ourColor;\n"
//"void main()\n"
//"{\n"
//"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"ourColor = aColor;\n"
//"}\0";
//
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"in vec3 ourColor;\n"
//"void main()\n"
//"{\n"
//"FragColor = vec4(ourColor, 1.0f);\n"
//"}\0";
//
//const char* fragmentShaderSource2 = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
//"}\0";

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
	glfwSwapInterval(5);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
	
	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);
	//// check for shader compile errors
	//int success;
	//char infoLog[512];
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}

	//// fragment shader
	//unsigned int fragmentShader, fragmentShader2;
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	//glCompileShader(fragmentShader);
	//glCompileShader(fragmentShader2);
	//// check for shader compile errors
	//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}

	//// link shaders
	//unsigned int shaderProgram, shaderProgram2;
	//shaderProgram = glCreateProgram();
	//shaderProgram2 = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);
	//
	//glAttachShader(shaderProgram2, vertexShader);
	//glAttachShader(shaderProgram2, fragmentShader2);
	//glLinkProgram(shaderProgram2);
	//// check for linking errors
	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success)
	//{
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	//	std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	//}
	//
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
	//glDeleteShader(fragmentShader2);
	{
		// set up vertex data (and buffer(s)) and configure vertex attributes
		//float vertices[] = {
		//	-0.5f, -0.5f, 0.0f,	//left
		//	0.5f, -0.5f, 0.0f,	//right
		//	0.0f,  0.5f, 0.0f	//top
		//};
		//float vertices[] = {
		//	0.5f, 0.5f, 0.0f,	//top right
		//	0.5f, -0.5f, 0.0f,	//bottom right
		//	-0.5f, -0.5f, 0.0f,	//bottom left
		//	-0.5f, 0.5f, 0.0f	//top left
		//};
		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		float vertices[] = {
			//position			//color
			-0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,	//0
			0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,	//1
			-0.45f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	//2
			-0.9f, 0.3f, 0.0f, 0.5f, 0.4f, 0.1f,	//3
		};
		float vertices2[] = {
			0.0f, -0.5f, 0.0f,
			0.9f, -0.5f, 0.0f,
			0.45f, 0.5f, 0.0f
		};
		/*unsigned int VAO, VBO, EBO;
		unsigned int VAOs[2], VBOs[2];
		unsigned int VAOs[2], VBOs[2], EBO;
		glGenVertexArrays(2, VAOs);
		glGenBuffers(2, VBOs);*/

		VertexArray VA1;
		VertexBuffer VB1(vertices, sizeof(vertices));
		/*glGenBuffers(2, VBOs);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);*/

		{
			VertexBufferLayout layout;
			layout.Push(GL_FLOAT, 3);
			layout.Push(GL_FLOAT, 3);
			VA1.AddBuffer(VB1, layout);
		}
		IndexBuffer IB(indices, 6);
		/*glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

		VertexArray VA2;
		VertexBuffer VB2(vertices2, sizeof(vertices2));
		/*glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
		glEnableVertexAttribArray(0);*/

		{
			VertexBufferLayout layout;
			layout.Push(GL_FLOAT, 3);
			VA2.AddBuffer(VB2, layout);
		}

		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		/*glBindVertexArray(VAOs[0]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glBindVertexArray(VAOs[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/


		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		//glBindVertexArray(0);

		// uncomment this call to draw in wireframe polygons.
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		Shader shader("basic");
		float r = 0.5f;
		float inc = 0.05f;
		Renderer renderer;
		// render loop
		while (!glfwWindowShouldClose(window))
		{
			// render
			renderer.Clear();

			// input
			processInput(window);

			// draw our first triangle
			if (r > 1.0f)
				inc = -0.05f;
			else if (r < 0.0f)
				inc = 0.05f;
			r += inc;
			shader.Bind();
			shader.SetUniform3f("u_Color", r, 0.2f, 0.8f);

			//VA1.Bind();// seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
			//GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
			/*glDrawArrays(GL_TRIANGLES, 0, 3);
			glUseProgram(shaderProgram2);
			glBindVertexArray(VAOs[1]);
			glDrawArrays(GL_TRIANGLES, 0, 3);*/
			renderer.Draw(VA1, IB, shader);

			/*VA2.Bind();
			GLCALL(glDrawArrays(GL_TRIANGLES, 0, 3));*/
			renderer.Draw(VA2, shader);
			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			glfwPollEvents();
			glfwSwapBuffers(window);
		}

		// optional: de-allocate all resources once they've outlived their purpose:
		/*glDeleteVertexArrays(2, VAOs);
		glDeleteBuffers(2, VBOs);
		glDeleteVertexArrays(2, VAOs);
		glDeleteBuffers(2, VBOs);
		glDeleteBuffers(1, &EBO);
		glDeleteProgram(shaderProgram2);*/

	}
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

