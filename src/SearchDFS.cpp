#include "SearchDFS.h"

/**
 * TODO: 
 */

SearchDFS::SearchDFS(const Grid* grid, GridCell start, GridCell end)
    : grid(grid), start(start), end(end), goal(false)
{
    this->init();
}

SearchDFS::~SearchDFS()
{
}

void SearchDFS::step()
{
    if (this->done())
    {
        return;
    }

    NodeDFS* node = this->open[this->open.size() - 1]; // peek

    if (node->state == this->end)
    {
        this->goal = true;
        return;
    }

    if ( // (short circuit)
        this->expand(node, UP) || 
        this->expand(node, RIGHT) || 
        this->expand(node, DOWN) || 
        this->expand(node, LEFT)
    )
    {
        return;
    }

    // Dead end node, pop it
    delete node;
    this->open.pop_back();
}

void SearchDFS::finish()
{
}

bool SearchDFS::done()
{
    return this->open.size() == 0 || this->goal;
}

const std::vector<Node*> SearchDFS::getOpen()
{
    std::vector<Node*> nodeVec(this->open.size());
    for (int i = 0; i < open.size(); i++)
    {
        nodeVec[i] = (Node*) this->open[i];
    }

    return nodeVec;
}

const std::vector<Node*> SearchDFS::getClosed()
{
    std::vector<Node*> empty;
    return empty;
}

const std::vector<Node*> SearchDFS::getSolution()
{
    if (!goal)
    {
        std::vector<Node*> empty;
        return empty;
    }
    else
    {
        return this->getOpen();
    }
}

void SearchDFS::init()
{
    NodeDFS* initial = new NodeDFS;
    initial->parent = nullptr;
    initial->state = this->start;
    this->open.push_back(initial);
}

/**
 * True if was able to expand node, else false.
 */
bool SearchDFS::expand(NodeDFS* node, Action act)
{
    GridCell nextState = doAction(node->state, act);

    bool alreadyExploredState = (node->SearchedUp && act == UP) || (node->SearchedRight && act == RIGHT) || (node->SearchedDown && act == DOWN) || (node->SearchedLeft && act == LEFT);
    bool isIllegalAction = !isLegalAction(this->grid, node->state, act);
    if (isIllegalAction || alreadyExploredState)
    {
        return false;
    }

    // Prevent infinite loops
    for (int i = 0; i < this->open.size(); i++)
    {
        bool isAlreadyOpenState = this->open[i]->state == nextState;
        if (isAlreadyOpenState)
        {
            return false;
        }
    }

    NodeDFS* child = new NodeDFS;
    child->parent = node;
    child->state = nextState;
    
    // Note: Prevents backtracking of child onto parent. Technically not needed
    //          since already taken care of by checking for duplicate state.
    //          However, we know 100% that child should never back track on to
    //          parent. So this will prevent 1/4 of O(n) checks on open list.
    if (act == UP)
    {
        child->SearchedDown = true;
        node->SearchedUp = true;
    }
    else if (act == RIGHT)
    {
        child->SearchedLeft = true;
        node->SearchedRight = true;
    }
    else if (act == DOWN)
    {
        child->SearchedUp = true;
        node->SearchedDown = true;
    }
    else // act == LEFT
    {
        child->SearchedRight = true;
        node->SearchedLeft = true;
    }

    this->open.push_back(child);

    return true;
}