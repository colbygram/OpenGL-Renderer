#include <glm.hpp>
#include <GLFW/glfw3.h>
#include "../Camera/Camera.hpp"

namespace System::Time {
	float GetDeltaTime();
}

namespace System::Cam {
	void Update(Camera& camera, glm::vec2 mouse_delta, float sens, float clamp);
}

namespace System::Mouse {
	glm::vec2 GetDelta(GLFWwindow* window);
}