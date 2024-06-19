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
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;

// camera @Deprecated
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f; // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // main=============================================================================
    // shader
    Shader shading("src/glsl/vs.glsl", "src/glsl/fs.glsl");
    Shader lightShading("src/glsl/vs.glsl", "src/glsl/lightFs.glsl");

    float vertices[] = {
        //     ---- 位置 ----  --法向量---     ---- 颜色 ----     - 纹理坐标 -
        -0.5f, -0.5f, -0.5f, /**/ 0.0f, 0.0f, -1.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, /**/ 0.0f, 0.0f, -1.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, /**/ 0.0f, 0.0f, -1.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, /**/ 0.0f, 0.0f, -1.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, /**/ 0.0f, 0.0f, -1.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, /**/ 0.0f, 0.0f, -1.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 0.0f, 0.0f,
        /**/
        -0.5f, -0.5f, 0.5f, /**/ 0.0f, 0.0f, 1.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, /**/ 0.0f, 0.0f, 1.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, /**/ 0.0f, 0.0f, 1.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, /**/ 0.0f, 0.0f, 1.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, /**/ 0.0f, 0.0f, 1.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, /**/ 0.0f, 0.0f, 1.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 0.0f, 0.0f,
        /**/
        -0.5f, 0.5f, 0.5f, /**/ -1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, /**/ -1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, /**/ -1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, /**/ -1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, /**/ -1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, /**/ -1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 1.0f, 0.0f,
        /**/
        0.5f, 0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, /**/ 1.0f, 0.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 1.0f, 0.0f,
        /**/
        -0.5f, -0.5f, -0.5f, /**/ 0.0f, -1.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, /**/ 0.0f, -1.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, /**/ 0.0f, -1.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, /**/ 0.0f, -1.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, /**/ 0.0f, -1.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, /**/ 0.0f, -1.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 0.0f, 1.0f,
        /**/
        -0.5f, 0.5f, -0.5f, /**/ 0.0f, 1.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, /**/ 0.0f, 1.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, /**/ 0.0f, 1.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, /**/ 0.0f, 1.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, /**/ 0.0f, 1.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, /**/ 0.0f, 1.0f, 0.0f, /**/ 1.0f, 0.5f, 0.31f, /**/ 0.0f, 1.0f};

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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // 没用

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(9 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // normal vec
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,11 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(3);

    // light=====
    unsigned int lightVAO, lightVBO;

    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &lightVBO);

    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // texture====
    unsigned int texture,
        texture2;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(false);
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
        glm::vec3(2.0f, 2.0f, -2.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)};

    // mouse
    // direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    // direction.y = sin(glm::radians(pitch));
    // irection.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

    // Colors
    glm::vec3 coral(1.0f, 0.5f, 0.31f);

    glm::vec3 lightColow1(1.0f, 1.0f, 1.0f);
    glm::vec3 toyColor(1.0f, 0.5f, 0.31f);
    glm::vec3 result = lightColow1 * toyColor; // = (1.0f, 0.5f, 0.31f);
    // part2============================================================================

    glm::vec3 lightColorw(1.0f, 1.0f, 1.0f);
    glm::vec3 toyColor2(1.0f, 0.5f, 0.31f);
    glm::vec3 result2 = lightColorw * toyColor2; // = (1.0f, 0.5f, 0.31f);

    //   main=============================================================================
    //  life circle
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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
        // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);

        unsigned int modelLoc = glGetUniformLocation(shading.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(shading.ID, "view");

        // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        shading.setMat4("projection", projection);

        // light pos
        glm::vec3 lightPos(1.0f, 1.0f, 1.0f);
        // camera/view transformation
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 2; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shading.setMat4("model", model);
            shading.setVec3("lightPos", lightPos);
            shading.setVec3("viewPos", cameraPos);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        lightShading.use();
        glBindVertexArray(lightVAO);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.5f));
        lightShading.setMat4("projection", projection);
        lightShading.setMat4("view", view);
        lightShading.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
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

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}