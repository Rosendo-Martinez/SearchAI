#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Shader.h"


std::string readFile(const char* path)
{
    std::string file;
    std::ifstream ifs (path); // open file

    if (!ifs.is_open()) // error check
    {
        std::cout << "Error: couldn't read file: " << path << std::endl;
        return file;
    }

    // load file to buffer
    std::stringstream ss; 
    ss << ifs.rdbuf();

    // close file
    ifs.close();

    // return file as string
    return ss.str();
}

Shader::Shader() : ID(0)
{
}

/**
 * Compiles and links shader program.
 * 
 * Logs errors.
 */
void Shader::compile(const char* vsPath, const char* fsPath)
{
    std::string strVertexShader = readFile(vsPath);
    std::string strFragmentShader = readFile(fsPath);
    const char *vertexShaderSource = strVertexShader.c_str();
    const char *fragmentShaderSource = strFragmentShader.c_str();

    // build and compile our shader program

    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    this->ID = shaderProgram;
}

void Shader::use()
{
    glUseProgram(this->ID);
}

void Shader::setVector(const char* name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}