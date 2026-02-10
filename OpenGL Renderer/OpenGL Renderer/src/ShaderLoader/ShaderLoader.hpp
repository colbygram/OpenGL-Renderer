#ifndef SHADERLOADER_HPP
#define SHADERLOADER_HPP

#include <string>

namespace Shader::Load {
	unsigned int CreateShaderProgram(std::string   vs_shader_file_path,  //vertex shader file path
									 std::string   fs_shader_file_path); //fragment shader file path
}

#endif