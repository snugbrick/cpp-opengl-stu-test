#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glslReader.hpp"

GLuint  loadShaderFromFile(const std::string& filename, GLenum shaderType) {
    std::string shaderSource = readShaderFromFile(filename);
    const char* shaderSourceCStr = shaderSource.c_str();

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSourceCStr, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Error compiling shader (" << filename << "): " << infoLog << std::endl;
    }

    return shader;
}

std::string readShaderFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}