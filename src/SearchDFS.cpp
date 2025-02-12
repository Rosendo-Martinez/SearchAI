#include "SearchDFS.h"
#include <iostream>


SearchDFS::SearchDFS(const Grid* grid, GridCell start, GridCell end)
    : grid(grid), start(start), end(end)
{
    this->init();
}

SearchDFS::~SearchDFS()
{
}

void SearchDFS::step()
{
    std::cout << "Before Step: \n";
    std::cout << "    Open: " << this->open.size() << '\n';
    std::cout << "    Closed: " << this->closed.size() << '\n';
    if (this->done())
    {
        return;
    }

    bool hitMaxDepth = (this->open.size() == 0);
    if (hitMaxDepth)
    {
        for (int i = 0; i < this->closed.size(); i++)
        {
            delete closed[i];
        }
        closed.clear();

        this->init();
        return;
    }

    bool backTracking = (closed.size() != 0) && (closed.back()->depth >= open.back()->depth);
    if (backTracking)
    {
        Node* node = closed.back();
        closed.pop_back();
        delete node; 

        return;
    }

    Node* toExplore = this->open.back();
    this->open.pop_back();
    this->closed.push_back(toExplore);

    bool nodeIsAtGoal = toExplore->state == this->end;
    if (nodeIsAtGoal)
    {
        this->goal = toExplore;
        this->foundGoal = true;
        return;
    }

    this->expand(toExplore, UP);
    this->expand(toExplore, RIGHT);
    this->expand(toExplore, DOWN);
    this->expand(toExplore, LEFT);

    // std::cout << "After Step: \n";
    // std::cout << "    Open: " << this->open.size() << '\n';
    // std::cout << "    Closed: " << this->closed.size() << '\n';
}

void SearchDFS::finish()
{
}

bool SearchDFS::done()
{
    return (this->open.size() == 0 && this->CURRENT_MAX_DEPTH == this->MAX_DEPTH) || this->foundGoal;
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
    std::vector<Node*> nodeVec(this->closed.size());
    for (int i = 0; i < closed.size(); i++)
    {
        nodeVec[i] = (Node*) this->closed[i];
    }

    return nodeVec;
}

const std::vector<Node*> SearchDFS::getSolution()
{
    if (!this->foundGoal)
    {
        std::vector<Node*> empty;
        return empty;
    }
    else
    {
        return this->closed;
    }
}

void SearchDFS::init()
{
    Node* initial = new Node;
    initial->parent = nullptr;
    initial->state = this->start;
    initial->depth = 0;
    this->CURRENT_MAX_DEPTH++;
    this->open.push_back(initial);
}

/**
 * True if was able to expand node, else false.
 */
void SearchDFS::expand(Node* node, Action act)
{
    bool childAtMaxDepth = node->depth + 1 == this->CURRENT_MAX_DEPTH;
    if (childAtMaxDepth)
    {
        return;
    }

    bool isIllegalAction = !isLegalAction(this->grid, node->state, act);
    if (isIllegalAction)
    {
        return;
    }

    GridCell childState = doAction(node->state, act);

    for (int i = 0; i < this->open.size(); i++)
    {
        bool foundDuplicateState = childState == this->open[i]->state;
        if (foundDuplicateState)
        {
            return;
        }
    }

    for (int i = 0; i < this->closed.size(); i++)
    {
        bool foundDuplicateState = childState == this->closed[i]->state;
        if (foundDuplicateState)
        {
            return;
        }
    }

    Node* child = new Node;
    child->state = childState;
    child->depth = node->depth + 1;
    child->parent = node;

    this->open.push_back(child);
}