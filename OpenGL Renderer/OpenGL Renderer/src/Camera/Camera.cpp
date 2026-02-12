#include "Camera.hpp"

#include <gtc/matrix_transform.hpp>

//https://gamedev.stackexchange.com/questions/190054/how-to-calculate-the-forward-up-right-vectors-using-the-rotation-angles
//Calculated my own using trigonometry
void Camera::Update()
{
	m_forward.x = glm::cos(glm::radians(m_pitch)) * glm::sin(glm::radians(m_yaw));
	m_forward.y = glm::sin(glm::radians(m_pitch));
	m_forward.z = glm::cos(glm::radians(m_pitch)) * -glm::cos(glm::radians(m_yaw));

	m_right.x = glm::cos(glm::radians(m_yaw));
	m_right.y = 0;
	m_right.z = glm::sin(glm::radians(m_yaw));

	m_up = glm::cross(m_forward, m_right);
}

void Camera::AddYaw(const float yaw)
{
	m_yaw += yaw;
}

void Camera::AddPitch(const float pitch)
{
	m_pitch += pitch;
}

void Camera::AddRoll(const float roll)
{
	m_roll += roll;
}

void Camera::AddPosition(const glm::vec3 position)
{
	m_position += position;
}

void Camera::SetPosition(const glm::vec3 position)
{
	m_position = position;
}

glm::vec3 Camera::GetPosition() const
{
	return m_position;
}

glm::vec3 Camera::GetForward() const
{
	return m_forward;
}

glm::vec3 Camera::GetRight() const
{
	return m_right;
}

glm::vec3 Camera::GetUp() const
{
	return m_up;
}

void Camera::SetYaw(const float yaw)
{
	m_yaw = yaw;
}

void Camera::SetPitch(const float pitch)
{
	m_pitch = pitch;
}

void Camera::SetRoll(const float roll)
{
	m_roll = roll;
}

float Camera::GetYaw() const
{
	return m_yaw;
}

float Camera::GetPitch() const
{
	return m_pitch;
}

float Camera::GetRoll() const
{
	return m_roll;
}

void Camera::SetFOV(const float fov)
{
	m_fov = fov;
}

void Camera::SetNear(const float near)
{
	m_near = near;
}

void Camera::SetFar(const float far)
{
	m_far = far;
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(m_position, m_position + m_forward, glm::vec3(0,1,0));
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	return glm::perspective(m_fov, 800.0f / 600.0f, m_near, m_far);
}
