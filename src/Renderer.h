#include "SquareRenderer.h"
#include "LineRenderer.h"
#include "Grid.h"
#include <glm/glm.hpp>

class Renderer
{
public:
    Renderer();

    SquareRenderer squareRenderer;
    LineRenderer lineRenderer;
    float GRID_WIDTH;
    float GRID_HEIGHT;

    void drawGrid(const Grid& grid);
    void drawGridLines(const Grid& grid);
    void drawCell(const GridCell& cell, const Grid& grid, const glm::vec3& color);

private:
};