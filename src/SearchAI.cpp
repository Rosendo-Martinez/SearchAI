#include "SearchAI.h"
#include <queue>
#include <iostream>

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

struct Node
{
    GridCell state;
    Node* parent;
};

enum Action
{
    // up is -y
    // right is +x
    UP, DOWN, LEFT, RIGHT
};

GridCell doAction(GridCell state, Action act)
{
    if (act == UP)
    {
        state.row--; 
    }
    else if (act == DOWN)
    {
        state.row++;
    }
    else if (act == LEFT)
    {
        state.col--;
    }
    else // act == RIGHT
    {
        state.col++;
    }
    return state;
}

bool isValidAction(GridCell state, Action act, const std::vector<Node*>& closed, const Grid& grid)
{
    GridCell nextState = doAction(state, act);

    if // out of bounds
    (
        nextState.col < 0 ||
        nextState.row < 0 ||
        nextState.col >= grid.getNumberOfColumns() ||
        nextState.row >= grid.getNumberOfRows()
    )
    {
        return false;
    }

    if (grid.get(state.row, state.col) != grid.get(nextState.row, nextState.col)) // same value/color
    {
        return false;
    }

    for (const auto& n : closed) // already explored state
    {
        if (n->state.col == nextState.col && n->state.row == nextState.row)
        {
            return false;
        }
    }

    return true;
}

std::vector<GridCell> searchBFS(GridCell start, GridCell end, const Grid& grid)
{

    std::vector<Node*> closed;
    std::queue<Node*> open;

    Node* initial = new Node;
    initial->parent = nullptr;
    initial->state = start;
    open.push(initial);
    initial = nullptr;

    // WARNING: make sure to clean up nodes in heap

    while (true)
    {
        if (open.empty()) // no solution
        {
            // Free memory 
            for (Node* &n : closed)
            {
                delete n;
                n = nullptr;
            }
            while (!open.empty())
            {
                Node* &n = open.front();
                open.pop();

                delete n;
                n = nullptr;
            }

            std::vector<GridCell> empty;
            return empty;
        }

        Node* n = open.front();
        open.pop();

        if (n->state.row == end.row && n->state.col == end.col) // at goal
        {
            // create solution list
            std::vector<GridCell> solution;
            Node* cur = n;
            while (cur != nullptr)
            {
                solution.push_back(cur->state);
                cur = cur->parent;
            }

            // Free memory
            for (Node* &n : closed)
            {
                delete n;
                n = nullptr;
            }
            while (!open.empty())
            {
                Node* &n = open.front();
                open.pop();

                delete n;
                n = nullptr;
            }
            delete n;
            n = nullptr;

            return solution;
        }

        // Expand node

        closed.push_back(n);
        if (isValidAction(n->state, UP, closed, grid))
        {
            Node* child = new Node;
            child->state = doAction(n->state, UP);
            child->parent = n;
            open.push(child);
        }
        if (isValidAction(n->state, DOWN, closed, grid))
        {
            Node* child = new Node;
            child->state = doAction(n->state, DOWN);
            child->parent = n;
            open.push(child);
        }
        if (isValidAction(n->state, LEFT, closed, grid))
        {
            Node* child = new Node;
            child->state = doAction(n->state, LEFT);
            child->parent = n;
            open.push(child);
        }
        if (isValidAction(n->state, RIGHT, closed, grid))
        {
            Node* child = new Node;
            child->state = doAction(n->state, RIGHT);
            child->parent = n;
            open.push(child);
        }
    }
}