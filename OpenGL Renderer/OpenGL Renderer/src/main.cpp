#include <iostream>
//GLFW Includes and macros
#define GLFW_DLL
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
//glad Includes and macros
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
//GLM math library using c++ module
import glm;

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

//Triangle vertices
float vertice_data[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

//Vertex Shader Code source
const char* vertex_shader_source =
"#version 330 core                                  \n"
"layout (location = 0) in vec3 aPos;                \n"
"void main()                                        \n"
"{                                                  \n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}                                                  \0";

//Fragment Shader Code source
const char* fragment_shader_source =
"#version 330 core                           \n"
"out vec4 FragColor;                         \n"
"void main()                                 \n"
"{                                           \n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}                                           \0";


int main(void) {
	std::cout << "Lets live life to the fullest\n\n";
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

	//This function binds the target GL_ARRAY_BUFFER to the buffer object, linking the buffer object ID to that target buffer, which describes how that buffer will be used
	//Only one binding per buffer target is allowed and whenever a new buffer object is associated to a buffer target, any previous binding will be broken
	//But a buffer object can be bound to multiple targets, meaning that the memory associated to the buffer object can be used to store multiple types of data (vertexes, shaders, etc.)
	//The GL_ARRAY_BUFFER target is bound to the VBO buffer object, which states that VBO will be responsible for storing the vertex data
	//Whenever the target GL_ARRAY_BUFFER is called to buffer vertex data, the VBO memory location on the GPU will be referenced
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Sending vertice_data to the VBO buffer by using the GL_ARRAY_BUFFER target
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertice_data), vertice_data, GL_STATIC_DRAW);


	///////////MAKING SHADERS/////////////////
	
	//Create shader object that will then have the vertex shader code provided to it
	unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);

	//Attach the vertex_shader_source to the vertex_shader_id so that the source code is sent into the created shader object
	glShaderSource(vertex_shader_id, 1, &vertex_shader_source, nullptr);

	//Tell the program to compile the previously setup vertex shader code
	glCompileShader(vertex_shader_id);

	//Check the success of the compiling of the vertex shader. if not successful then print errors
	int success;
	char info_log[512];
	glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex_shader_id, 512, nullptr, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
	}
	success = 0;

	//Use similar process for making fragment shader
	unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_id, 1, &fragment_shader_source, nullptr);
	glCompileShader(fragment_shader_id);
	glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment_shader_id, 512, nullptr, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
	}
	success = 0;

	//Need to make shader program that will link each part of the shaders we made
	unsigned int shader_program_id = glCreateProgram();
	//Attach each of the shaders we made to the shader program
	glAttachShader(shader_program_id, vertex_shader_id);
	glAttachShader(shader_program_id, fragment_shader_id);
	//Link the individual shaders in the shader program
	glLinkProgram(shader_program_id);

	//Check the success of linking the program
	glGetProgramiv(shader_program_id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program_id, 512, nullptr, info_log);
		std::cout << "ERROR::SHADER::LINKING_FAILED\n" << info_log << std::endl;
	}
	success = 0;

	//Tell OpenGL to use our newly created shader program when doing shader calculations
	glUseProgram(shader_program_id);

	//After compiling the program and using it, we can delete the previously built shaders
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	//Settting vertex attributes so that OpenGL can tell the GPU and shaders how to interpret the vertice data provided
	//The first parameter is which vertex atribute location we want to use for our data.
	//	This value was specified in the vertex shader using the layout (location = 0) ...
	//The following parameters set how many generic values (# of floats in this situation) will be in our vertex attribute
	//GL_FLOAT specifies the type of our values in the vertex attribute and GL_FALSE specifies that we don't want to normalize our values
	//3*sizeof(float) specifies the stride of our array, aka telling OpenGL when our next vertex attribute will be in our array.
	//Since our array is tightly packed with vertex attributes, we can technically leave that value as 0 and OpenGL will interpret it automatically
	//The final parameter is a specified offset for the start of our array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	///////////////////RENDER LOOP/////////////////////////////
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