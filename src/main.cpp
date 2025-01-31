#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "SquareRenderer.h"
#include "Grid.h"

bool initialize(GLFWwindow* &window, unsigned int width, unsigned int height);
void processInput(GLFWwindow *window);

int main()
{
    // Window
    GLFWwindow* window = nullptr;
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 800;

    if (!initialize(window, SCR_WIDTH, SCR_HEIGHT))
    {
        return -1;
    }

    // Shader, and renderer
    Shader shader;
    shader.compile("./shaders/square.vs", "./shaders/square.fs");
    SquareRenderer renderer(shader);

    struct ProjectionConfig
    {
        float top = 800.0f;
        float bottom = 0.0f;
        float left = 0.0f;
        float right = 800.0f;
        float near = 1.0f;
        float far = -1.0f;
    } projConfig;

    glm::mat4 projection = glm::ortho(projConfig.left, projConfig.right, projConfig.bottom, projConfig.top, projConfig.near, projConfig.far);
    shader.use();
    shader.setMat4("projection", projection);

    // just log out the result for now
    Grid grid(2,2);

    /**
     * 0 1
     * 1 0
     */
    grid.set(0, 0, 0);
    grid.set(0, 1, 1);
    grid.set(1, 0, 1);
    grid.set(1, 1, 0);

    std::cout << "Grid:\n";
    std::cout << grid.get(0,0) << ' ' << grid.get(0,1) << '\n';
    std::cout << grid.get(1,0) << ' ' << grid.get(1,1) << '\n';

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::vec3 color = glm::vec3(0.7f, 0.1f, 0.2f);
        glm::vec3 translate = glm::vec3(400.f, 400.f, 0.0f);
        glm::vec2 scale = glm::vec2(400.f);

        renderer.draw(color, translate, scale);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

/**
 * Initializes window and GLAD.
 * 
 * Returns false if something went wrong, and logs error.
 */
bool initialize(GLFWwindow* &window, unsigned int width, unsigned int height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "A1", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }    
    glViewport(0, 0, width, height);

    return true;
}