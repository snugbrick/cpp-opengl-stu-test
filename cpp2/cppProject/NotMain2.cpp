#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include "GlslReader.hpp"

#include <iostream>
#include <alloca.h>
#include <math.h>
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const float vertices[] = {
    -0.5f,
    -0.5f,
    0.5f,
    -0.5f,
    0.0f,
    0.5f,
};

static unsigned int compileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char *msg = (char *)alloca(len * sizeof(char));
        glGetShaderInfoLog(id, len, &len, msg);
        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? " vertex " : " fragment ")
                  << "shader" << std::endl;
        std::cout << msg << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main()
{
    GLFWwindow *window;
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "myOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //=======================buffers=========================
    unsigned int indices[] = {1,
                              2,
                              3,
                              2,
                              3,
                              4};
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    //================Textures==============================
    unsigned int tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    //======================================================
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void *)0);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    std::string vertexShader =
        "#version 330 core\n"
        "layout(location = 0)\n"
        "in vec4 position;\n"
        "out vec4 color;\n"
        "void main()\n"
        "{ gl_Position= position;\n"
        "  color = vec4(1.0, 0.0, 0.0, 1.0);}\n";

    std::string fragmentShader =
        "#version 330 core\n"
        "in vec4 color;\n"
        "out vec4 FColor;\n"
        "void main()\n"
        "{ FColor = color; }\n";

    unsigned int shader = createShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 黑色背景

    //=================vector=======================
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);

    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 trans2 = glm::rotate(trans2, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    trans2 = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
    vec = trans * vec;
    std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;

    auto cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    //==============================================

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glUseProgram(shader);
        // glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}