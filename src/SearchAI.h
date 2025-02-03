#include <vector>
// #include "Grid.h"

struct GridCell
{
    unsigned int row;
    unsigned int col;
};

std::vector<GridCell> search(GridCell start, GridCell end);