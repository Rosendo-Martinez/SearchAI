#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

// #include "Shader.h"
// #include "SquareRenderer.h"
#include "GridRawData.h"
// #include "LineRenderer.h"
#include "SearchAI.h"
#include "Renderer.h"

const glm::vec3 SOLUTION_COLOR = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 CLOSED_CELL = glm::vec3(0.725f, 0.024f, 0.035f);
const glm::vec3 OPEN_CELL = glm::vec3(0.976f, 0.792f, 0.012f);
const glm::vec3 MOUSE_COLOR = glm::vec3(0.0f, 0.75f, 1.0f);

glm::vec2 mousePos;

glm::vec2 pathStart;
glm::vec2 pathEnd;
unsigned int selectedPathEndpoints = 0;

bool reInitAI = true;
SearchAI ai;
bool usingBFS = true;

float lastAnimation = 0.0f;
const float ANIMATION_INTERVAL = 0.4f; // seconds
bool animate = false;

Grid grid;

bool initialize(GLFWwindow* &window, unsigned int width, unsigned int height);
void processInput(GLFWwindow *window);
void loadGrid(Grid& grid, const char* rawData);
GridCell getCellThatMouseIsOn(Grid& grid,const glm::vec2& mousePos, float gridWidth, float gridHeight);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

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

    // Events
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);

    // // Shader, and renderer
    // Shader squareShader;
    // squareShader.compile("./shaders/square.vs", "./shaders/square.fs");
    // SquareRenderer squareRenderer;
    // squareRenderer.init(squareShader);

    // Shader lineShader;
    // lineShader.compile("./shaders/line.vs", "./shaders/line.fs");
    // LineRenderer lineRenderer;
    // lineRenderer.init(lineShader);

    Renderer renderer;
    renderer.GRID_HEIGHT = SCR_HEIGHT;
    renderer.GRID_WIDTH = SCR_WIDTH;

    initializeGridData();
    grid.createGrid(gridData->rows, gridData->cols);
    loadGrid(grid, gridData->rawData);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();

        if (selectedPathEndpoints == 2 && !ai.done() && animate && currentFrame + ANIMATION_INTERVAL >= lastAnimation)
        {
            ai.step();
            lastAnimation = currentFrame;
        }

        if (reInitAI && selectedPathEndpoints == 2)
        {
            ai.init(getCellThatMouseIsOn(grid, pathStart, SCR_WIDTH, SCR_HEIGHT), getCellThatMouseIsOn(grid, pathEnd, SCR_WIDTH, SCR_HEIGHT), &grid, usingBFS);
            reInitAI = false;
        }

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // drawGrid(grid, squareRenderer, SCR_WIDTH, SCR_HEIGHT);
        renderer.drawGrid(grid);

        if (selectedPathEndpoints == 2)
        {
            std::vector<GridCell> openList = ai.getOpen();
            for (GridCell c : openList)
            {
                // drawCell(c, grid, SCR_WIDTH, SCR_HEIGHT, squareRenderer, OPEN_CELL);
                renderer.drawCell(c, grid, OPEN_CELL);
            }
            std::vector<GridCell> closedList = ai.getClosed();
            for (GridCell c : closedList)
            {
                // drawCell(c, grid, SCR_WIDTH, SCR_HEIGHT, squareRenderer, CLOSED_CELL);
                renderer.drawCell(c, grid, CLOSED_CELL);
            }
            std::vector<GridCell> solution = ai.getSolution();
            for (GridCell c : solution)
            {
                // drawCell(c, grid, SCR_WIDTH, SCR_HEIGHT, squareRenderer, SOLUTION_COLOR);
                renderer.drawCell(c, grid, SOLUTION_COLOR);
            }
        }

        GridCell mouseCell = getCellThatMouseIsOn(grid, mousePos, SCR_WIDTH, SCR_HEIGHT);
        // drawCell(mouseCell, grid, SCR_WIDTH, SCR_HEIGHT, squareRenderer, MOUSE_COLOR);
        renderer.drawCell(mouseCell, grid, MOUSE_COLOR);

        GridCell pathStartCell = getCellThatMouseIsOn(grid, pathStart, SCR_WIDTH, SCR_HEIGHT);
        GridCell pathEndCell = getCellThatMouseIsOn(grid, pathEnd, SCR_WIDTH, SCR_HEIGHT);
        if (selectedPathEndpoints == 1)
        {
            // drawCell(pathStartCell, grid, SCR_WIDTH, SCR_HEIGHT, squareRenderer, SOLUTION_COLOR);
            renderer.drawCell(pathStartCell, grid, SOLUTION_COLOR);
        }
        else if (selectedPathEndpoints == 2)
        {
            // drawCell(pathStartCell, grid, SCR_WIDTH, SCR_HEIGHT, squareRenderer, SOLUTION_COLOR);
            // drawCell(pathEndCell, grid, SCR_WIDTH, SCR_HEIGHT, squareRenderer, SOLUTION_COLOR);
            renderer.drawCell(pathStartCell, grid, SOLUTION_COLOR);
            renderer.drawCell(pathEndCell, grid, SOLUTION_COLOR);
        }

        // drawGridLines(grid, lineRenderer, SCR_WIDTH, SCR_HEIGHT);
        renderer.drawGridLines(grid);

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

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        if (selectedPathEndpoints == 0 || selectedPathEndpoints == 2)
        {
            pathStart = glm::vec2(xpos, ypos);
            selectedPathEndpoints = 1;
        }
        else 
        {
            pathEnd = glm::vec2(xpos,ypos);
            selectedPathEndpoints = 2;
            reInitAI = true;
        }
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        ai.step();
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        if (ai.done() && selectedPathEndpoints == 2)
        {
            reInitAI = true;
            animate = true;
        }
        else
        {
            animate = !animate;
        }
    }
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
    {
        usingBFS = !usingBFS;
        reInitAI = true;
    }
}