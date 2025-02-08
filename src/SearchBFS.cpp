#include "SearchBFS.h"

// Note: I'm switching too one time use instances!

SearchBFS::SearchBFS(const Grid* grid, GridCell start, GridCell end)
    : grid(grid), start(start), end(end), open(false), goal(nullptr)
{
    this->init();
}

SearchBFS::~SearchBFS()
{
    for (Node* node : this->closed)
    {
        delete node;
    }

    while (!open.isEmpty())
    {
        Node* node = open.pop();
        delete node;
    }
}

void SearchBFS::init()
{
    Node* initial = new Node;
    initial->parent = nullptr;
    initial->state = this->start;
    this->open.push(initial);
}

void SearchBFS::step()
{
    if (this->done())
    {
        return;
    }

    Node* current = this->open.pop();
    closed.push_back(current);

    if (this->end == current->state)
    {
        this->foundGoal = true;
        this->goal = current;
        return;
    }


}

void SearchBFS::expand(Node* node, Action act, std::vector<Node*>& openVec)
{
    if (!isLegalAction(this->grid, node->state, act))
    {
        return;
    }

    Node child = expandHelper(node, act);

    
}