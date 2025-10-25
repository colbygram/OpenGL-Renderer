#include <iostream>
//GLFW Includes and macros
#define GLFW_DLL
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
//glad Includes and macros
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
//GLM math library
#include <glm.hpp>

//Error callback printed to console whenever error occurs in GLFW
void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

//resize callback whenever the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(void) {
	std::cout << "Lets live life to the fullest\n";
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	//Initial window size
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Learning OpenGL", nullptr, nullptr);
	if (!window) {
		printf("Error: window could not be initialized!");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Render loop
	while (!glfwWindowShouldClose(window)) {
		//Check inputs
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

		//////////////Render commands//////////////////

		//Sets the color that OpenGL will clear with
		glClearColor(0.5, 0.6, 0.9, 1);
		//Specify which buffer to clear
		glClear(GL_COLOR_BUFFER_BIT);

		//CheckEvents and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}