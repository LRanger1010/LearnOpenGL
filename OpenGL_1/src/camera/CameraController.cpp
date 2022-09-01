#include "pch.h"
#include "Camera.h"

glm::vec3 GetCameraPosition()
{
	return camera->GetCameraPos();
}

glm::vec3 GetCameraDirection()
{
	return camera->GetCameraDirection();
}

CameraController::CameraController()
	:m_CameraSpeed(0), m_CameraRotateSpeed(0), m_Pitch(0), m_Yaw(0)
{
	m_Camera = new Camera;
	camera = m_Camera;
}

CameraController::~CameraController()
{
	if (m_Camera)
		delete(m_Camera);
	camera = nullptr;
}

void CameraController::Update(float deltaTime)
{
	m_CameraSpeed = 2.5f * deltaTime;
	m_CameraRotateSpeed = 5.0f * deltaTime;
}

void CameraController::UpdateCameraPos(const glm::vec3& deltaPos)
{
	m_Camera->UpdateCameraPos(deltaPos);
}

void CameraController::UpdateCameraDir(float pitch, float yaw)
{
	/*m_Pitch = pitch;
	m_Yaw = yaw;*/
	m_Camera->UpdateCameraDir(pitch, yaw);
}

void CameraController::UpdateCameraFov(float fov)
{
	m_Camera->UpdateCameraFov(fov);
}