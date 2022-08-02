#include<glad\glad.h>
#include<glfw3.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<stdio.h>
#include "Render.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int width = 800;
const unsigned int height = 600;

const std::string shaderDir = "res/shaders/";
const std::string shaderExt = ".shader";

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


struct ShaderSource
{
	std::string vertexShaderSource;
	std::string fragmentShaderSource;
};

static ShaderSource ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);
	std::string line;
	std::stringstream ss[2];
	enum class ShaderType {
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1,
	};
	ShaderType type = ShaderType::NONE;
	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	return{ ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "Shader!" << std::endl;
		std::cout << message << std::endl;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

static ShaderSource FindShader(const std::string& shaderName)
{
	std::string filepath = shaderDir + shaderName + shaderExt;
	return ParseShader(filepath);
}

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
		ShaderSource source = FindShader("basic");
		unsigned int shaderProgram = CreateShader(source.vertexShaderSource, source.fragmentShaderSource);

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
		//unsigned int VAO, VBO, EBO;
		//unsigned int VAOs[2], VBOs[2];
		unsigned int VAOs[2], VBOs[2], EBO;
		/*glGenVertexArrays(2, VAOs);
		glGenBuffers(2, VBOs);*/
		glGenVertexArrays(2, VAOs);
		glBindVertexArray(VAOs[0]);
		VertexBuffer VBs[2];
		VBs[0].Bind(vertices, sizeof(vertices));
		/*glGenBuffers(2, VBOs);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);*/
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		IndexBuffer IB(indices, 6);
		/*glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

		glBindVertexArray(VAOs[1]);
		VBs[1].Bind(vertices2, sizeof(vertices2));
		/*glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);*/
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
		glEnableVertexAttribArray(0);

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
		glEnableVertexAttribArray(0);*/
		/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/


		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		//glBindVertexArray(0);

		// uncomment this call to draw in wireframe polygons.
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		int location = glGetUniformLocation(shaderProgram, "u_Color");
		ASSERT(location != -1);
		float r = 0.5f;
		float inc = 0.05f;
		// render loop
		while (!glfwWindowShouldClose(window))
		{
			// render
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// input
			processInput(window);

			// draw our first triangle
			glUseProgram(shaderProgram);
			if (r > 1.0f)
				inc = -0.05f;
			else if (r < 0.0f)
				inc = 0.05f;
			r += inc;
			GLCALL(glUniform3f(location, r, 0.2f, 0.8f));

			GLCALL(glBindVertexArray(VAOs[0]));// seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			/*glUseProgram(shaderProgram2);
			glBindVertexArray(VAOs[1]);
			glDrawArrays(GL_TRIANGLES, 0, 3);*/
			GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

			GLCALL(glBindVertexArray(VAOs[1]));
			GLCALL(glDrawArrays(GL_TRIANGLES, 0, 3));
			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			glfwPollEvents();
			glfwSwapBuffers(window);
		}

		// optional: de-allocate all resources once they've outlived their purpose:
		/*glDeleteVertexArrays(2, VAOs);
		glDeleteBuffers(2, VBOs);*/
		glDeleteVertexArrays(2, VAOs);
		glDeleteBuffers(2, VBOs);
		glDeleteBuffers(1, &EBO);
		glDeleteProgram(shaderProgram);
		//glDeleteProgram(shaderProgram2);

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

