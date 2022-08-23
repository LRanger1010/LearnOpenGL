#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"
#define MATRIX_VP GetVP()
#define WINDOW GetWindow()
#define CAMERA_POS GetCameraPosition()

static glm::mat4 matrix_vp;
static GLFWwindow* window = nullptr;
static float pitch = 0;
static float yaw = 0;
static bool isFirstMouse = true;
static float lastX = 400.0f;
static float lastY = 300.0f;
static float mouseSensitivity = 0.05f;

glm::mat4 GetVP();
GLFWwindow* GetWindow();
glm::vec3 GetCameraPosition();
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

class Camera
{
public:
	Camera();
	~Camera();

	inline glm::mat4 GetMatrixVP() const
	{
		glm::mat4 view = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraDir, m_CameraUp);
		glm::mat4 projection = glm::perspective(glm::radians(m_Fov), m_Aspect, m_Near, m_Far);
		return projection * view;
	}
	inline glm::vec3 GetCameraPos() const { return m_CameraPos; }
	inline glm::vec3 GetCameraDirection() const { return m_CameraDir; }
	inline glm::vec3 GetCameraUp() const { return m_CameraUp; }
	inline float GetCameraFov() const { return m_Fov; }

	void SetCameraPos(float x, float y, float z);
	void SetCameraDir(float x, float y, float z);
	void SetCameraFov(float fov);
	void SetCameraAspect(unsigned int width, unsigned int height);
	void SetCameraNearFar(float near, float far);
	void UpdateCameraPos(const glm::vec3& deltaPos);
	void UpdateCameraDir(float pitch, float yaw);
	void UpdateCameraFov(float fov);

private:
	glm::vec3 m_CameraPos;
	glm::vec3 m_CameraDir;
	glm::vec3 m_CameraUp;
	float m_Fov;
	float m_Aspect;
	float m_Near;
	float m_Far;
};
static Camera* camera = nullptr;

class CameraController
{
public:
	CameraController(GLFWwindow* win);
	~CameraController();

	inline Camera* GetCamera() const{ return m_Camera; }

	void Update(float deltaTime);

private:
	Camera* m_Camera;
	float m_CameraSpeed;
	float m_CameraRotateSpeed;
	void processInput();
};