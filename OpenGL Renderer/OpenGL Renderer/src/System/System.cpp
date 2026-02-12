#include "System.hpp"

//#include <GLFW/glfw3.h>

float System::Time::GetDeltaTime()
{
	static float previous_frame_time;
	float delta_time = (float)glfwGetTime() - previous_frame_time;
	previous_frame_time = (float)glfwGetTime();
	return delta_time;
}

void System::Cam::Update(Camera& cam, glm::vec2 mouse_delta, float sens, float clamp)
{
	cam.AddPitch(-(mouse_delta.y * sens));
	cam.AddYaw(mouse_delta.x * sens);

	if (cam.GetPitch() > clamp) cam.SetPitch(clamp);
	else if (cam.GetPitch() < -clamp) cam.SetPitch(-clamp);

	cam.Update();
}

glm::vec2 System::Mouse::GetDelta(GLFWwindow* window)
{
	static float previous_x, previous_y;
	double current_mouse_x, current_mouse_y;
	glfwGetCursorPos(window, &current_mouse_x, &current_mouse_y);
	glm::vec2 mouse_delta{};
	mouse_delta.x = (float)current_mouse_x - previous_x;
	mouse_delta.y = (float)current_mouse_y - previous_y;
	previous_x = (float)current_mouse_x;
	previous_y = (float)current_mouse_y;
	return mouse_delta;
}
