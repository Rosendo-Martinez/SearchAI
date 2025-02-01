#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "SquareRenderer.h"
#include "Grid.h"

const glm::vec3 CELL_COLORS[] = 
{
    glm::vec3(0.0f), // 0
    glm::vec3(1.0f)  // 1 
};

const unsigned int GRID_1_ROWS = 3;
const unsigned int GRID_1_COLS = 3;
const char* GRID_1 = 
{
    "0 1 0 "
    "1 0 1 "
    "0 1 0 "
};

bool initialize(GLFWwindow* &window, unsigned int width, unsigned int height);
void processInput(GLFWwindow *window);
void drawGrid(const Grid& grid, SquareRenderer& renderer, float gridWidth, float gridHeight);
void loadGrid(Grid& grid, const char* rawData);

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

    Grid grid(GRID_1_ROWS, GRID_1_COLS);
    loadGrid(grid, GRID_1);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        drawGrid(grid, renderer, SCR_WIDTH, SCR_HEIGHT);

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

void drawGrid(const Grid& grid, SquareRenderer& renderer, float gridWidth, float gridHeight)
{
    const float cellWidth = gridWidth / (float) grid.getNumberOfColumns();
    const float cellHeight = gridHeight / (float) grid.getNumberOfRows();

    for (unsigned int row = 0; row < grid.getNumberOfRows(); row++)
    {
        for (unsigned int col = 0; col < grid.getNumberOfColumns(); col++)
        {
            float xTranslation = ((float) col) * cellWidth;
            float yTranslation = ((float) ((grid.getNumberOfRows() - 1) - row)) * cellHeight;
            glm::vec3 color = CELL_COLORS[grid.get(row,col)];

            renderer.draw(color, glm::vec2(xTranslation, yTranslation), glm::vec2(cellWidth, cellHeight));
        }
    }
}

void loadGrid(Grid& grid, const char* rawData)
{
    unsigned int i = 0;
    for (unsigned int row = 0; row < grid.getNumberOfRows(); row++)
    {
        for (unsigned int col = 0; col < grid.getNumberOfColumns(); col++)
        {
            unsigned int value = rawData[i] - '0';
            grid.set(row, col, value);

            i += 2;
        }
    }
}