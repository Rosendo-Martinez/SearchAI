#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include "Shader.h"
#include "SquareRenderer.h"
#include "Grid.h"
#include "GridRawData.h"
#include "LineRenderer.h"

const glm::vec3 CELL_COLORS[] = 
{
    glm::vec3(0.0f), // 0
    glm::vec3(1.0f)  // 1 
};

struct GridCell
{
    unsigned int row;
    unsigned int col;
};

glm::vec2 mousePos;

bool initialize(GLFWwindow* &window, unsigned int width, unsigned int height);
void processInput(GLFWwindow *window);
void drawGrid(const Grid& grid, SquareRenderer& renderer, float gridWidth, float gridHeight);
void drawGridLines(const Grid& grid, LineRenderer& renderer, float gridWidth, float gridHeight);
void loadGrid(Grid& grid, const char* rawData);
GridCell getCellThatMouseIsOn(Grid& grid,const glm::vec2& mousePos, float gridWidth, float gridHeight);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void drawCell(const GridCell& cell, Grid& grid, float gridWidth, float gridHeight, SquareRenderer& renderer);

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
    glfwSetCursorPosCallback(window, cursor_position_callback);

    // Shader, and renderer
    Shader shader;
    shader.compile("./shaders/square.vs", "./shaders/square.fs");
    SquareRenderer renderer(shader);

    Shader lineShader;
    lineShader.compile("./shaders/line.vs", "./shaders/line.fs");
    LineRenderer lineRenderer(lineShader);

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
    lineShader.use();
    lineShader.setMat4("projection", projection);

    initializeGridData();
    Grid grid(gridData->rows, gridData->cols);
    loadGrid(grid, gridData->rawData);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        drawGrid(grid, renderer, SCR_WIDTH, SCR_HEIGHT);
        drawGridLines(grid, lineRenderer, SCR_WIDTH, SCR_HEIGHT);

        GridCell mouseCell = getCellThatMouseIsOn(grid, mousePos, SCR_WIDTH, SCR_HEIGHT);
        drawCell(mouseCell, grid, SCR_WIDTH, SCR_HEIGHT, renderer);

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

void drawGridLines(const Grid& grid, LineRenderer& renderer, float gridWidth, float gridHeight)
{
    const float cellWidth = gridWidth / (float) grid.getNumberOfColumns();
    const float cellHeight = gridHeight / (float) grid.getNumberOfRows();
    const glm::vec3 color (0.1f, 0.01f, 0.9f);

    // Draw horizontal lines
    for (unsigned int i = 0; i < grid.getNumberOfRows() + 1; i++)
    {
        float y = cellHeight * i;
        glm::vec2 start (0, y);
        glm::vec2 end   (gridWidth, y);

        renderer.draw(color, start, end);
    }

    // Draw vertical lines
    for (unsigned int i = 0; i < grid.getNumberOfColumns() + 1; i++)
    {
        float x = cellWidth * i;
        glm::vec2 start (x, 0);
        glm::vec2 end   (x, gridHeight);

        renderer.draw(color, start, end);
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

GridCell getCellThatMouseIsOn(Grid& grid,const glm::vec2& mousePos, float gridWidth, float gridHeight)
{
    const float cellWidth = gridWidth / (float) grid.getNumberOfColumns();
    const float cellHeight = gridHeight / (float) grid.getNumberOfRows();

    GridCell cell;
    cell.row = std::floor(mousePos.y / cellHeight);
    cell.col = std::floor(mousePos.x / cellWidth);

    return cell;
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    mousePos.x = xpos;
    mousePos.y = ypos;
}

void drawCell(const GridCell& cell, Grid& grid, float gridWidth, float gridHeight, SquareRenderer& renderer)
{
    const float cellWidth = gridWidth / (float) grid.getNumberOfColumns();
    const float cellHeight = gridHeight / (float) grid.getNumberOfRows();
    float xTranslation = ((float) cell.col) * cellWidth;
    float yTranslation = ((float) ((grid.getNumberOfRows() - 1) - cell.row)) * cellHeight;

    renderer.draw(glm::vec3(0.9, 0.01, 0.01), glm::vec2(xTranslation, yTranslation), glm::vec2(cellWidth, cellHeight));
}