#include "Camera.h"

GLFWwindow* GetWindow()
{
	return window;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (camera)
	{
		float fov = camera->GetCameraFov();
		if (fov >= 1.0f && fov <= 45.0f)
			fov -= yoffset;
		fov = glm::clamp(fov, 1.0f, 45.0f);
		camera->UpdateCameraFov(fov);
	}
}

CameraController::CameraController(GLFWwindow* win)
	:m_CameraSpeed(0)
{
	m_Camera = new Camera;
	window = win;
	camera = m_Camera;
	//glfwSetCursorPosCallback(win, mouse_callback);
	//glfwSetScrollCallback(win, scroll_callback);
}

CameraController::~CameraController()
{
	if (m_Camera)
		delete(m_Camera);
	window = nullptr;
	camera = nullptr;
}

void CameraController::Update(float deltaTime)
{
	m_CameraSpeed = 2.5f * deltaTime;
	processInput();
}

void CameraController::processInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (m_Camera)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			m_Camera->UpdateCameraPos(m_CameraSpeed * m_Camera->GetCameraDirection());
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			m_Camera->UpdateCameraPos(-m_CameraSpeed * m_Camera->GetCameraDirection());
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			m_Camera->UpdateCameraPos(glm::normalize(glm::cross(m_Camera->GetCameraUp(), m_Camera->GetCameraDirection())) * m_CameraSpeed);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			m_Camera->UpdateCameraPos(glm::normalize(glm::cross(m_Camera->GetCameraDirection(), m_Camera->GetCameraUp())) * m_CameraSpeed);

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			pitch += m_CameraSpeed;
			pitch = glm::clamp(pitch, -89.0f, 89.0f);
			camera->UpdateCameraDir(pitch, yaw);
		}
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		{
			pitch -= m_CameraSpeed;
			pitch = glm::clamp(pitch, -89.0f, 89.0f);
			camera->UpdateCameraDir(pitch, yaw);
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			yaw -= m_CameraSpeed;
			camera->UpdateCameraDir(pitch, yaw);
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			yaw += m_CameraSpeed;
			camera->UpdateCameraDir(pitch, yaw);
		}
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		{
			float fov = camera->GetCameraFov();
			if (fov >= 1.0f && fov <= 45.0f)
				fov -= m_CameraSpeed;
			fov = glm::clamp(fov, 1.0f, 45.0f);
			camera->UpdateCameraFov(fov);
		}
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		{
			float fov = camera->GetCameraFov();
			if (fov >= 1.0f && fov <= 45.0f)
				fov += m_CameraSpeed;
			fov = glm::clamp(fov, 1.0f, 45.0f);
			camera->UpdateCameraFov(fov);
		}
	}
}