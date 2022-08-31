#include "pch.h"
#include "WindowsWindow.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window* Window::Create(const WindowProp& prop)
{
	return new WindowsWindow(prop);
}

WindowsWindow::WindowsWindow(const WindowProp& prop)
	:m_ClearColor{ 0.1f, 0.1f, 0.1f, 1.0f }
{
	m_Data.Width = prop.Width;
	m_Data.Height = prop.Height;
	m_Data.Name = prop.Name;
	Init();
}

WindowsWindow::~WindowsWindow()
{
	Shutdown();
}

void WindowsWindow::OnUpdate()
{
	float deltaTime = 0;
	float lastFrame = 0;
	while (!glfwWindowShouldClose(m_Window))
	{
		float curFrame = (float)glfwGetTime();
		deltaTime = curFrame - lastFrame;
		lastFrame = curFrame;
		m_TestMenu->OnUpdate(deltaTime);

		m_CameraController->Update(deltaTime);

		// render
		m_Renderer->Clear(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
		m_TestMenu->OnRender();

		// input
		//processInput(window);

		ImGui_ImplGlfwGL3_NewFrame();

		m_TestMenu->OnGUI();
		ImGui::ColorEdit4("clear color", m_ClearColor);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
}

void WindowsWindow::SetVSync(bool enabled)
{
	if(enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	m_VSyncEnabled = enabled;
}

bool WindowsWindow::IsVSync()
{
	return m_VSyncEnabled;
}

void WindowsWindow::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Name.c_str(), NULL, NULL);
	if (m_Window == NULL)
	{
		std::cout << "Failed to Create GLFW Window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(m_Window);
	glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
	SetVSync(true);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	GLCALL(glEnable(GL_BLEND));
	GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCALL(glEnable(GL_DEPTH_TEST));

	InitImGui();
	InitTest();
	m_Renderer = std::make_unique<Renderer>();
	m_CameraController = std::make_unique<CameraController>(m_Window);
}

void WindowsWindow::Shutdown()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}

void WindowsWindow::InitTest()
{
	m_TestMenu = std::make_unique<test::TestMenu>();
	m_TestMenu->RegisterTest<test::TestTexture2D>("2D Texture");
	m_TestMenu->RegisterTest<test::TestBatchRenderingTexture2D>("Batch Rendering Texture");
	m_TestMenu->RegisterTest<test::TestDynamicBatching>("Dynamic Batching");
	m_TestMenu->RegisterTest<test::Test3DModel>("3D Model");
	m_TestMenu->RegisterTest<test::TestPhoneShading>("Blinn-Phong Shading");
	m_TestMenu->RegisterTest<test::TestMultiLights>("Multi-Lights");
}

void WindowsWindow::InitImGui()
{
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(m_Window, true);
	ImGui::StyleColorsDark();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
