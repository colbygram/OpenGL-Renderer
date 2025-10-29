#include "ShaderLoader.h"

#include <iostream>

std::string LoadShader(std::string file_path) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::ifstream vShaderFile;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(file_path);

        std::stringstream vShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    return vertexCode;
}