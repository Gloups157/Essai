#include "engine/renderer/Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    std::string vertexShaderString;
    std::string fragmentShaderString;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    // ensure ifstream objects can throw exceptions:
    vertexShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);
        std::stringstream vertexShaderStream, fragmentShaderStream;
        // read file’s buffer contents into streams
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexShaderString = vertexShaderStream.str();
        fragmentShaderString = fragmentShaderStream.str();
    }
    catch(std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ:" << e.what() << std::endl;
    }

    const char* vertexShaderSource = vertexShaderString.c_str();
    const char* fragmentShaderSource = fragmentShaderString.c_str();
    createShaderProgram(vertexShaderSource, fragmentShaderSource);
}

std::string Shader::shaderTypeToString(GLenum type) {
    switch (type) {
        case GL_VERTEX_SHADER:
            return "VERTEX";
        case GL_FRAGMENT_SHADER:
            return "FRAGMENT";
        default:
            return std::to_string(type);
    }
}

unsigned int Shader::compileShader(GLenum shaderType, const char* objectShaderSource) {
    // Create id for object shader and link it with the shader source. Then compile it
    unsigned int objectShader = glCreateShader(shaderType);
    glShaderSource(objectShader, 1, &objectShaderSource, NULL);
    glCompileShader(objectShader);
    // Verify if shader compile or log an error
    int success;
    char infoLog[512];
    glGetShaderiv(objectShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(objectShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << shaderTypeToString(shaderType) << "::COMPILATION_FAILED" << infoLog << std::endl;
    }
    return objectShader;
}

unsigned int Shader::createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
    int success;
    char infoLog[512];
    // create and compile vertex/fragment shader
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    // Create id for shader program. Then we attach the vertex shader and fragment shader to the shader program
    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    // Link them, so the fragment can have inputs from vertex shader ouputs
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    // Verify if program link or log an error
    if(!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED" << infoLog << std::endl;
    }
    // Free shader memory
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return id;
}

void Shader::use() {
    glUseProgram(id);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setUint(const std::string &name, unsigned int value) const {
    glUniform1ui(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setVec2(const std::string &name, const glm::vec2& value) const {
    glUniform2f(glGetUniformLocation(id, name.c_str()), value.x, value.y);
}

void Shader::setVec3(const std::string &name, const glm::vec3& value) const {
    glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);
}

void Shader::setMat4(const std::string &name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(id,name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setIntArray(const std::string &name, const int arr) const {
    glUniform1iv(glGetUniformLocation(id,name.c_str()), 1, GL_FALSE, arr)
}
