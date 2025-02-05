#include "SearchAI.h"


/**
 * Very simple search AI. It just goes straight to the goal.
 * 
 * Solution returned backwards in vector.
 */
std::vector<GridCell> searchDumb(GridCell start, GridCell end)
{
    std::vector<GridCell> solution;

    GridCell current = start;
    while (true)
    {
        solution.push_back(current);

        if (current.row == end.row && current.col == end.col) // goal found
        {
            return solution;
        }

        // Move to next grid cell

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

bool isValidAction(GridCell state, Action act, const std::vector<Node*>& closed, const Grid& grid, const std::vector<GridCell>& open)
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

    for (const auto& n : closed) // in closed list
    {
        if (n->state.col == nextState.col && n->state.row == nextState.row)
        {
            return false;
        }
    }

    for (GridCell c : open) // in open list
    {
        if (c.col == nextState.col && c.row == nextState.row)
        {
            return false;
        }
    }

    return true;
}

void SearchAI::init(GridCell start, GridCell end, Grid* grid, bool useBFS)
{
    // Free memory
    for (Node* n : closed)
    {
        delete n;
    }
    this->closed.clear();
    while (!open.isEmpty())
    {
        Node* n = open.pop();

        delete n;
    }

    // init.

    this->start = start;
    this->end = end;
    this->grid = grid;
    this->foundGoal = false;
    this->goal = nullptr;
    this->usingBFS = useBFS;
    this->open = StackOrQueue(!useBFS); // BFS uses queue, DFS uses stack

    // init. state
    Node* initial = new Node;
    initial->parent = nullptr;
    initial->state = start;
    this->open.push(initial);
}

void SearchAI::step()
{
    // std::cout << "STEP\n";

    if (this->done()) // no solution / done
    {
        // std::cout << "  Open Empty or Found Goal\n";
        return;
    }

    Node * n = this->open.pop();
    closed.push_back(n);

    if (n->state.row == this->end.row && n->state.col == this->end.col) // at goal
    {
        // std::cout << "  At goal\n";
        this->foundGoal = true;
        this->goal = n;
        return;
    }

    // Expand node

    const std::vector<GridCell> openList = this->getOpen();
    if (isValidAction(n->state, UP, closed, *this->grid, openList))
    {
        // std::cout << "  Do Action Up\n";
        Node* child = new Node;
        child->state = doAction(n->state, UP);
        child->parent = n;
        this->open.push(child);
    }
    if (isValidAction(n->state, DOWN, closed, *this->grid, openList))
    {
        // std::cout << "  Do Action Down\n";
        Node* child = new Node;
        child->state = doAction(n->state, DOWN);
        child->parent = n;
        this->open.push(child);
    }
    if (isValidAction(n->state, LEFT, closed, *this->grid, openList))
    {
        // std::cout << "  Do Action Left\n";
        Node* child = new Node;
        child->state = doAction(n->state, LEFT);
        child->parent = n;
        this->open.push(child);
    }
    if (isValidAction(n->state, RIGHT, closed, *this->grid, openList))
    {
        // std::cout << "  Do Action Right\n";
        Node* child = new Node;
        child->state = doAction(n->state, RIGHT);
        child->parent = n;
        this->open.push(child);
    }   
}

std::vector<GridCell> SearchAI::getOpen()
{
    return this->open.getGridCells();
}

std::vector<GridCell> SearchAI::getClosed()
{
    std::vector<GridCell> toReturn;

    for (Node* n : this->closed)
    {
        toReturn.push_back(n->state);
    }

    return toReturn;
}

std::vector<GridCell> SearchAI::getSolution()
{
    std::vector<GridCell> sol;

    if (!foundGoal) // no solution 
    {
        return sol;
    }

    Node* cur = this->goal;
    while (cur != nullptr)
    {
        sol.push_back(cur->state);
        cur = cur->parent;
    }

    return sol;
}

// true if found goal, else false
bool SearchAI::done()
{
    return foundGoal || this->open.isEmpty();
}

StackOrQueue::StackOrQueue()
    : isStack(true)
{
}

StackOrQueue::StackOrQueue(bool isStack)
    : isStack(isStack)
{
}

Node* StackOrQueue::pop()
{
    Node* node;
    if (this->isStack)
    {
        node = this->stack.top();
        this->stack.pop();
    }
    else
    {
        node = this->queue.front();
        this->queue.pop();
    }

    return node;
}

void StackOrQueue::push(Node* node)
{
    if (this->isStack)
    {
        this->stack.push(node);
    }
    else
    {
        this->queue.push(node);
    }
}

bool StackOrQueue::isEmpty() const
{
    if (this->isStack)
    {
        return this->stack.size() == 0;
    }
    else
    {
        return this->queue.size() == 0;
    }
}

std::vector<GridCell> StackOrQueue::getGridCells()
{
    // Make copy of stack/queue
    std::vector<Node*> copy;
    while (!this->isEmpty())
    {
        copy.push_back(this->pop());
    }

    // Create GridCell list
    std::vector<GridCell> gridCells;
    for (Node* n : copy)
    {
        gridCells.push_back(n->state);
    }

    // Restore stack/queue
    if (this->isStack)
    {
        for (int i = copy.size() - 1; i > -1; i--)
        {
            this->push(copy[i]);
        }
    }
    else
    {
        for (int i = 0; i < copy.size(); i++)
        {
            this->push(copy[i]);
        }
    }

    return gridCells;
}