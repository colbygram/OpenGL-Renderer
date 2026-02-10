#ifndef RESOURCES_HPP
#define RESOURCES_HPP

//GLFW Includes and macros
#define GLFW_DLL //Using GLFW DLL libraries
#define GLFW_INCLUDE_NONE //Tell GLFW not to include OpenGL stuff due to glad
#include <GLFW/glfw3.h>

//glad Includes and macros
#define GLAD_GL_IMPLEMENTATION //glad header only macro // includes function implementations
#include <glad/gl.h>

//GLM math library using c++ module
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc//type_ptr.hpp>

//STB file loader header library
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include "../ShaderLoader/ShaderLoader.hpp"

#endif