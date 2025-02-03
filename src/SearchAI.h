#include <vector>
#include "Grid.h"

struct GridCell
{
    unsigned int row;
    unsigned int col;
};

std::vector<GridCell> search(GridCell start, GridCell end);

std::vector<GridCell> searchBFS(GridCell start, GridCell end, const Grid& grid);