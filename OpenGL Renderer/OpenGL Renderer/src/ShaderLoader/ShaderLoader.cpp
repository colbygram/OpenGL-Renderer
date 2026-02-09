#include "ShaderLoader.h"

#include <iostream>
#include <glad/gl.h>

static std::string LoadShader(const std::string file_path) {
    
    std::string   vertexCode;
    std::ifstream shaderFile;
    // ensure ifstream objects can throw exceptions:
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        shaderFile.open(file_path);
        std::stringstream shaderStream;
        // read file's buffer contents into streams
        shaderStream << shaderFile.rdbuf();
        // close file handlers
        shaderFile.close();
        // convert stream into string
        vertexCode = shaderStream.str();
    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ::PATH = " + file_path << std::endl;
    }
    return vertexCode;
}

static bool CompileShader(const unsigned int shader_id, const std::string shader_type) 
{
    glCompileShader(shader_id);

    int success;
    char info_log[512];
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_id, 512, nullptr, info_log);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << "SHADER = " + shader_type + ":\n" << info_log << std::endl;
        return false;
    }
    return true;
}

static bool LinkShaderProgram(const unsigned int shader_program_id) {
    
    glLinkProgram(shader_program_id);

    int success;
    char info_log[512];
    glGetProgramiv(shader_program_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program_id, 512, nullptr, info_log);
        std::cout << "ERROR::SHADER::LINKING_FAILED\n" << info_log << std::endl;
        return false;
    }
    return true;
}

unsigned int Shader::Load::CreateShaderProgram(std::string   vs_shader_file_path,
                                 std::string   fs_shader_file_path)
{
    std::string vertex_str   = LoadShader(vs_shader_file_path),
                fragment_str = LoadShader(fs_shader_file_path);

    const char* vertex_source   = vertex_str.c_str();
    const char* fragment_source = fragment_str.c_str();

    unsigned int vertex_id   = glCreateShader( GL_VERTEX_SHADER ), 
                 fragment_id = glCreateShader(GL_FRAGMENT_SHADER);

    unsigned int return_program_id = 0;

    glShaderSource(vertex_id  , 1, &vertex_source  , nullptr);
    glShaderSource(fragment_id, 1, &fragment_source, nullptr);

    if (!CompileShader(vertex_id, "VERTEX") || !CompileShader(fragment_id, "FRAGMENT")) return_program_id = 0;

    unsigned int shader_program_id = glCreateProgram();
    
    glAttachShader(shader_program_id, vertex_id);
    glAttachShader(shader_program_id, fragment_id);
    
    if (!LinkShaderProgram(shader_program_id)) return_program_id = 0;
    else return_program_id = shader_program_id;

    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);

    return return_program_id;
}