#include "pch.h"
#include "WindowsWindow.h"


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
		ProcessInput();

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
	glfwSetWindowUserPointer(m_Window, this);
	glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
		auto ww = (WindowsWindow*)glfwGetWindowUserPointer(window);
		ww->OnWindowSizeCallback(width, height);
	});
	//glfwSetCursorPosCallback(m_Window, WindowsWindow::mouse_callback);
	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
		ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
	});
	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
		auto ww = (WindowsWindow*)glfwGetWindowUserPointer(window);
		ww->OnMouseScrollCallback(xoffset, yoffset);
		ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
	});
	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
	});
	glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int c) {
		ImGui_ImplGlfw_CharCallback(window, c);
	});
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
	GLCALL(glEnable(GL_STENCIL_TEST));

	InitImGui();
	InitTest();
	m_Renderer = std::make_unique<Renderer>();
	m_CameraController = std::make_unique<CameraController>();
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
	m_TestMenu->RegisterTest<test::TestModel>("Model");
	m_TestMenu->RegisterTest<test::TestGPUInstancing>("GPU Instancing");
}

void WindowsWindow::InitImGui()
{
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(m_Window, false);
	ImGui::StyleColorsDark();
}

void WindowsWindow::ProcessInput()
{
	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_Window, true);
	}
	if (m_CameraController)
	{
		auto camera = m_CameraController->GetCamera();
		float speed = m_CameraController->GetCameraSpeed();
		float rotateSpeed = m_CameraController->GetCameraRotateSpeed();
		float& pitch = m_CameraController->GetCameraPitch();
		float& yaw = m_CameraController->GetCameraYaw();

		if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
			m_CameraController->UpdateCameraPos(speed * camera->GetCameraDirection());
		if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
			m_CameraController->UpdateCameraPos(-speed * camera->GetCameraDirection());
		if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
			m_CameraController->UpdateCameraPos(glm::normalize(glm::cross(camera->GetCameraUp(), camera->GetCameraDirection())) * speed);
		if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
			m_CameraController->UpdateCameraPos(glm::normalize(glm::cross(camera->GetCameraDirection(), camera->GetCameraUp())) * speed);

		if (glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
 			pitch += rotateSpeed;
			pitch = glm::clamp(pitch, -89.0f, 89.0f);
			m_CameraController->UpdateCameraDir(pitch, yaw);
		}
		if (glfwGetKey(m_Window, GLFW_KEY_C) == GLFW_PRESS)
		{
			pitch -= rotateSpeed;
			pitch = glm::clamp(pitch, -89.0f, 89.0f);
			m_CameraController->UpdateCameraDir(pitch, yaw);
		}
		if (glfwGetKey(m_Window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			yaw -= rotateSpeed;
			m_CameraController->UpdateCameraDir(pitch, yaw);
		}
		if (glfwGetKey(m_Window, GLFW_KEY_E) == GLFW_PRESS)
		{
			yaw += rotateSpeed;
			m_CameraController->UpdateCameraDir(pitch, yaw);
		}
		if (glfwGetKey(m_Window, GLFW_KEY_Z) == GLFW_PRESS)
		{
			float fov = camera->GetCameraFov();
			if (fov >= 1.0f && fov <= 45.0f)
				fov -= speed;
			fov = glm::clamp(fov, 1.0f, 45.0f);
			m_CameraController->UpdateCameraFov(fov);
		}
		if (glfwGetKey(m_Window, GLFW_KEY_X) == GLFW_PRESS)
		{
			float fov = camera->GetCameraFov();
			if (fov >= 1.0f && fov <= 45.0f)
				fov += speed;
			fov = glm::clamp(fov, 1.0f, 45.0f);
			m_CameraController->UpdateCameraFov(fov);
		}
		if (glfwGetKey(m_Window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			m_CameraController->UpdateCameraPos(speed * camera->GetCameraUp());
		}
		if (glfwGetKey(m_Window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			m_CameraController->UpdateCameraPos(-speed * camera->GetCameraUp());
		}
	}
}

void WindowsWindow::OnWindowSizeCallback(int width, int height)
{
	glViewport(0, 0, width, height);
}

void WindowsWindow::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (camera)
	{
		if (isFirstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			isFirstMouse = false;
		}
		float xOffset = xpos - lastX;
		float yOffset = ypos - lastY;

		xOffset *= mouseSensitivity;
		yOffset *= mouseSensitivity;

		pitch += yOffset;
		yaw += xOffset;

		pitch = glm::clamp(pitch, -89.0f, 89.0f);

		camera->UpdateCameraDir(pitch, yaw);
	}
}

void WindowsWindow::OnMouseScrollCallback(double xoffset, double yoffset)
{
	if (m_CameraController)
	{
		float fov = m_CameraController->GetCamera()->GetCameraFov();
		if (fov >= 1.0f && fov <= 45.0f)
			fov -= (float)yoffset;
		fov = glm::clamp(fov, 1.0f, 45.0f);
		m_CameraController->UpdateCameraFov(fov);
	}
}
