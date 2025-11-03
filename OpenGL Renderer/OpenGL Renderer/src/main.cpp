//GLFW Includes and macros
#define GLFW_DLL //Using GLFW DLL libraries
#define GLFW_INCLUDE_NONE //Tell GLFW not to include GL stuff
#include <GLFW/glfw3.h>

//glad Includes and macros
#define GLAD_GL_IMPLEMENTATION //glad header only macro // includes function implementations
#include <glad/gl.h>

//GLM math library using c++ module
import glm;

#include <iostream>
#include "ShaderLoader/ShaderLoader.h"

//Triangle vertices
float vertice_data[] = {
	//Positions          Colors
	 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  
	 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f 
};

unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

int main(void) {
	std::cout << "Lets live life to the fullest\n\n";

	//Setting error callbacks using lamda expressions
	glfwSetErrorCallback(
		[](int error, const char* description)
		{
			fprintf(stderr, "Error: %s\n", description);
		}
	);

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

	//Setting Framebuffer size callbacks using lamda expressions
	glfwSetFramebufferSizeCallback(window, 
		[](GLFWwindow* window, int width, int height) 
		{
			glViewport(0, 0, width, height);
		}
	);

	//CREATING GPU MEMORY BUFFERS
	//You create a region of memory on a GPU using buffer objects.
	//You then use targets to tell the GPU what those buffers are used for
	//For example, i create a buffer object VBO_1 and then bind it to a GL_ARRAY_BUFFER which tells the GPU that the memory section of VBO_1 will be used for vertex data input

	//first vertex buffer object
	//This int stores the unique ID of the OpenGL object (buffer)
	unsigned int VBO;

	//This function creates the buffer object but it is not bound to a target buffer yet
	//This creates a buffer object which represents memory on the GPU
	glGenBuffers(1, &VBO);

	//A VAO or Vertex Array Object will store configurations of your vertex attributes and is basically a container for eahc of your vertex attrributes whenever you have them
	//so each index into the array can be seen as an index to an individual vertex attribute so index 0 might be vertex positions, while index 1 is vertex texture coords
	
	//VAO will also store when EnableVertexAttribArray was called and the VBO associated to that vertex attribute

	//Before binding our VBO, setup VAO so that it will store the data in an attribute pointer
	unsigned int VAO;
	//Generating 1 VAO and storing its reference ID
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//This function binds the target GL_ARRAY_BUFFER to the buffer object, linking the buffer object ID to that target buffer, which describes how that buffer will be used
	//Only one binding per buffer target is allowed and whenever a new buffer object is associated to a buffer target, any previous binding will be broken
	//But a buffer object can be bound to multiple targets, meaning that the memory associated to the buffer object can be used to store multiple types of data (vertexes, shaders, etc.)
	//The GL_ARRAY_BUFFER target is bound to the VBO buffer object, which states that VBO will be responsible for storing the vertex data
	//Whenever the target GL_ARRAY_BUFFER is called to buffer vertex data, the VBO memory location on the GPU will be referenced
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Sending vertice_data to the VBO buffer by using the GL_ARRAY_BUFFER target
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertice_data), vertice_data, GL_STATIC_DRAW);


	//Setting vertex attributes so that OpenGL can tell the GPU and shaders how to interpret the vertice data provided
	//The first parameter is which vertex attribute location we want to use for our data which is the index of the vertex attribute in the VAO array
	//	This value was specified in the vertex shader using the layout (location = 0) and is our first index in the VAO array
	 
	//The following parameters set how many generic values (# of floats in this situation) will be in our vertex attribute
	//GL_FLOAT specifies the type of our values in the vertex attribute and GL_FALSE specifies that we don't want to normalize our values
	
	//3*sizeof(float) specifies the stride of our array, aka telling OpenGL when our next vertex attribute will be in our array.
	//Since our array is tightly packed with vertex attributes, we can technically leave that value as 0 and OpenGL will interpret it automatically
	
	//The final parameter is a specified offset for the start of our array. The offset is determined through bytes

	//PERSONAL NOTES:
	//This function basically interprets our vertex attribute(position, texture coord, etc) in our buffers, because we may store multiple vertex attributes together
	//So this function would define how we interpet our vertex attribute of the position but we could have another vertex atrtribute of the texture coordinate and specify its
	//interpretation in the same function
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	//Enables the usage of the vertex attribute array at the given index in a VAO
	glEnableVertexAttribArray(0);

	//Setting up color vertex attributes in VBO
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	///////////MAKING SHADERS/////////////////
	unsigned int program_id = CreateShaderProgram("res/shaders/shader_placeholder.vert", "res/shaders/fragment_placeholder.frag");

	//Generating an element buffer object to store indice information
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	//When binding element buffer objects, a VAO will store this binding if it is currently bound
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Sets the color that OpenGL will clear with
	glClearColor(0.5, 0.6, 0.9, 1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	int vertexColorLocation = glGetUniformLocation(program_id, "ourColor");
	
	///////////////////RENDER LOOP/////////////////////////////
	while (!glfwWindowShouldClose(window)) {
		//Check inputs
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

		//////////////Render commands//////////////////
		
		float time = glfwGetTime();
		float green = abs(sin(time));
		float red = abs(sin(time-3.145f));
		float blue = abs(sin(time+3.145f));
		//Specify which buffer to clear
		glClear(GL_COLOR_BUFFER_BIT);
		//After setting up VAO, VBO and shaders to use those, we can finally render triangle to screen
		glUseProgram(program_id);
		//Sets uniform using location and inserts values. Must be called after UseProgram since it only works on active shader program
		glUniform4f(vertexColorLocation, red, green, blue, 1.0f);

		glBindVertexArray(VAO);
		//Specify that we are drawing triangles, the second argument is the starting index we'd like to begin drawing in our vertex array
		//The final parameter is how many vertices we will be drawing
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//CheckEvents and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(program_id);

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}