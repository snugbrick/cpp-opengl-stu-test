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

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // init
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GameTest", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //===================
    // register func
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // main=============================================================================
    // shader
    Shader shading("src/glsl/vs.glsl", "src/glsl/fs.glsl");

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

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    // buffer
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // texture====
    unsigned int texture, texture2;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("src/assets/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("src/assets/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    /*watch out here*/
    shading.use();
    glUniform1i(glGetUniformLocation(shading.ID, "texture"), 0);
    shading.setInt("texture2", 1);

    // vecs
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)};
    //  main=============================================================================
    // life circle
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/
        shading.use();
        /*watch out here */
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // create transformations :/
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        unsigned int modelLoc = glGetUniformLocation(shading.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(shading.ID, "view");

        // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        shading.setMat4("projection", projection);

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shading.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f); // 透视平截头体
        // mat and vec============================
        // glDrawArrays(GL_TRIANGLES, 0, 36);

        // events and change buffer
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // delete
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}