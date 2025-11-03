#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <sstream>
#include <string>
#include <fstream>

unsigned int CreateShaderProgram(std::string   vs_shader_file_path,  //vertex shader file path
					             std::string   fs_shader_file_path); //fragment shader file path

#endif
														/////PREVIOUS PROCESS OF MAKING SHADERS IN MAIN///////////

////Using LoadShader function to interpret separate shader files
	//std::string vertStr = LoadShader("res/shaders/shader_placeholder.vert");
	//std::string fragStr = LoadShader("res/shaders/fragment_placeholder.frag");
	//const char* vert_out = vertStr.c_str();
	//const char* frag_out = fragStr.c_str();
	//
	////Create shader object that will then have the vertex shader code provided to it
	//unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);

	////Attach the vertex_shader_source to the vertex_shader_id so that the source code is sent into the created shader object
	//glShaderSource(vertex_shader_id, 1, &vert_out, nullptr);

	////Tell the program to compile the previously setup vertex shader code
	//glCompileShader(vertex_shader_id);

	////Check the success of the compiling of the vertex shader. if not successful then print errors
	//int success;
	//char info_log[512];
	//glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success);
	//if (!success) {
	//	glGetShaderInfoLog(vertex_shader_id, 512, nullptr, info_log);
	//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
	//}
	//success = 0;

	////Use similar process for making fragment shader
	//unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragment_shader_id, 1, &frag_out, nullptr);
	//glCompileShader(fragment_shader_id);
	//glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success);
	//if (!success) {
	//	glGetShaderInfoLog(fragment_shader_id, 512, nullptr, info_log);
	//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
	//}
	//success = 0;

	////Need to make shader program that will link each part of the shaders we made
	//unsigned int shader_program_id = glCreateProgram();
	////Attach each of the shaders we made to the shader program
	//glAttachShader(shader_program_id, vertex_shader_id);
	//glAttachShader(shader_program_id, fragment_shader_id);
	////Link the individual shaders in the shader program
	//glLinkProgram(shader_program_id);

	////Check the success of linking the program
	//glGetProgramiv(shader_program_id, GL_LINK_STATUS, &success);
	//if (!success) {
	//	glGetProgramInfoLog(shader_program_id, 512, nullptr, info_log);
	//	std::cout << "ERROR::SHADER::LINKING_FAILED\n" << info_log << std::endl;
	//}
	//success = 0;

	////Tell OpenGL to use our newly created shader program when doing shader calculations
	////glUseProgram(shader_program_id);

	////After compiling the program and using it, we can delete the previously built shaders
	//glDeleteShader(vertex_shader_id);
	//glDeleteShader(fragment_shader_id);
