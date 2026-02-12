#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm.hpp>

class Camera
{
private:
	glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f),
		m_right = glm::vec3(1.0f, 0.0f, 0.0f),
		m_forward = glm::vec3(0.0f, 0.0f, -1.0f),
		m_position;

	float m_pitch = 0.0f, 
		m_yaw = 0.0f, 
		m_roll = 0.0f;

	float m_fov = 70.0f;

	float m_near = 0.1f, 
		m_far = 100.0f;
public:
	Camera() : m_position(glm::vec3(0.0f, 1.0f, 0.0f)) {}
	Camera(glm::vec3 position) : m_position(position) {}

	void Update();

	void AddYaw(const float yaw);
	void AddPitch(const float pitch);
	void AddRoll(const float roll);

	void AddPosition(const glm::vec3 position);

	void SetPosition(const glm::vec3 position);
	glm::vec3 GetPosition() const;
	glm::vec3 GetForward() const;
	glm::vec3 GetRight() const;
	glm::vec3 GetUp() const;

	void SetYaw(const float yaw);
	void SetPitch(const float pitch);
	void SetRoll(const float roll);

	float GetYaw() const;
	float GetPitch() const;
	float GetRoll() const;

	void SetFOV(const float fov);
	void SetNear(const float near);
	void SetFar(const float far);

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
};

#endif