#include "SearchAI.h"

// Solution returned backwards.
std::vector<GridCell> search(GridCell start, GridCell end)
{
    std::vector<GridCell> solution;

    GridCell current = start;
    while (true)
    {
        solution.push_back(current);

        if (current.row == end.row && current.col == end.col)
        {
            return solution;
        }

        if (current.col < end.col)
        {
            current.col++;
        }
        else if (current.col > end.col)
        {
            current.col--;
        }
        else if (current.row < end.row)
        {
            current.row++;
        }
        else // current.row > end.row
        {
            current.row--;
        }
    }
}