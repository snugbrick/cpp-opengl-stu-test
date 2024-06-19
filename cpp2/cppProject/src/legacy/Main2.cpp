#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <iostream>
#include <fstream>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GlslReader.hpp"

void processInput(GLFWwindow *window);
void frame_buffer_callback(GLFWwindow *window, int width, int height);

const unsigned int WIDTH = 1600;
const unsigned int HEIGHT = 900;

float vertices[] = {
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
    -0.5f, -0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 0.0f, 0.0f,
    /**/
    -0.5f, -0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 0.0f, 0.0f,
    /**/
    -0.5f, 0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.0f,
    /**/
    0.5f, 0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.0f,
    /**/
    -0.5f, -0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 0.0f, 1.0f,
    /**/
    -0.5f, 0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 0.0f, 1.0f};

int main()
{
    // init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Color Test", NULL, NULL);
    if (window == nullptr)
    {
        std::cout << "glfw window open failed" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, frame_buffer_callback);

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 1, &vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Shader shading("scr/glsl/newVs.glsl", "scr/glsl/newFs.glsl");

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shading.use();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void frame_buffer_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}