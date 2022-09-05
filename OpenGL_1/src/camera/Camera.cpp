#include "pch.h"
#include "Camera.h"

glm::mat4 GetVP()
{
	return matrix_vp;
}

Camera::Camera()
	:m_Fov(45.0f), m_Aspect((float)800/(float)600), m_Near(0.1f), m_Far(100.0f)
{
	m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	m_CameraDir = glm::vec3(0.0f, 0.0f, -1.0f);
	m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	matrix_vp = GetMatrixVP();
}

Camera::~Camera()
{

}

void Camera::SetCameraPos(float x, float y, float z)
{
	m_CameraPos.x = x;
	m_CameraPos.y = y;
	m_CameraPos.z = z;
}

void Camera::SetCameraDir(float x, float y, float z)
{
	m_CameraDir.x = x;
	m_CameraDir.y = y;
	m_CameraDir.z = z;
	m_CameraDir = glm::normalize(m_CameraDir);
}

void Camera::SetCameraFov(float fov)
{
	m_Fov = fov;
}

void Camera::SetCameraAspect(unsigned int width, unsigned int height)
{
	m_Aspect = (float)width / (float)height;
}

void Camera::SetCameraNearFar(float near, float far)
{
	m_Near = near;
	m_Far = far;
}

void Camera::UpdateCameraPos(const glm::vec3& deltaPos)
{
	m_CameraPos += deltaPos;
	matrix_vp = GetMatrixVP();
}

void Camera::UpdateCameraDir(float pitch, float yaw)
{
	float x = -glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw));
	float y = -glm::sin(glm::radians(pitch));
	float z = -glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
	SetCameraDir(x, y, z);
	glm::vec3 camera_right = glm::normalize(glm::cross(Up, m_CameraDir));
	m_CameraUp = glm::normalize(glm::cross(m_CameraDir, camera_right));
	matrix_vp = GetMatrixVP();
}

void Camera::UpdateCameraFov(float fov)
{
	SetCameraFov(fov);
	matrix_vp = GetMatrixVP();
}
