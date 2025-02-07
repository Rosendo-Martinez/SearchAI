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

        if (current == end) // goal found
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

Node* expand(Node* parent, Action act)
{
    Node* child = new Node;
    child->state = doAction(parent->state, act);
    child->parent = parent;
    child->depth = parent->depth + 1;
    
    return child;
}

bool isValidAction(GridCell state, Action act, const std::vector<Node*>& closed, const Grid& grid, const std::vector<GridCell>& open, unsigned int depth)
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

    for (const auto& aNode : closed) // in closed list
    {
        if (aNode->state == nextState && aNode->depth <= depth + 1)
        {
            return false;
        }
    }

    for (GridCell aCell : open) // in open list
    {
        if (aCell == nextState)
        {
            return false;
        }
    }

    return true;
}

void SearchAI::init(GridCell start, GridCell end, Grid* grid, SearchAIType ai)
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
    this->ai = ai;
    this->CUR_MAX_DEPTH = 0;

    if (ai == BFS)
    {
        this->open = StackOrQueue(false);
    }
    else if (ai == DFS || ai == ID_DFS)
    {
        this->open = StackOrQueue(true);
    }

    // init. state
    Node* initial = new Node;
    initial->parent = nullptr;
    initial->state = start;
    initial->depth = 0;
    this->open.push(initial);
}

void SearchAI::step()
{
    if (this->done()) // Found solution or no possible solution
    {
        return;
    }

    if (this->open.isEmpty()) // increase depth for ID-DFS
    {
        std::cout << "Reset ID-DFS\n";
        std::cout << "Open size: " << this->open.size() << '\n';
        std::cout << "Closed size: " << this->closed.size() << '\n';

        unsigned int temp = this->CUR_MAX_DEPTH;
        this->init(this->start, this->end, this->grid, ID_DFS); // reset
        this->CUR_MAX_DEPTH = temp + 1;
    }

    Node * current = this->open.pop();
    closed.push_back(current);

    if (this->end == current->state) // at goal
    {
        this->foundGoal = true;
        this->goal = current;
        return;
    }

    if (this->ai == ID_DFS && current->depth == CUR_MAX_DEPTH) // at max depth
    {
        return;
    }

    // Expand node

    const std::vector<GridCell> openList = this->getOpen();
    if (isValidAction(current->state, UP, closed, *this->grid, openList, current->depth))
    {
        this->open.push(expand(current, UP));
    }
    if (isValidAction(current->state, DOWN, closed, *this->grid, openList, current->depth))
    {
        this->open.push(expand(current, DOWN));
    }
    if (isValidAction(current->state, LEFT, closed, *this->grid, openList, current->depth))
    {
        this->open.push(expand(current, LEFT));
    }
    if (isValidAction(current->state, RIGHT, closed, *this->grid, openList, current->depth))
    {
        this->open.push(expand(current, RIGHT));
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
    if (this->ai == ID_DFS)
    {
        return foundGoal || (this->CUR_MAX_DEPTH == this->MAX_DEPTH && this->open.isEmpty());
    }
    else
    {
        return foundGoal || this->open.isEmpty();
    }
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

unsigned int StackOrQueue::size()
{
    return (this->isStack ? this->stack.size() : this->queue.size());
}