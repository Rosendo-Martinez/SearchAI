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

    for (int i = 0; i < this->closed.size(); i++)
    {
        if (child.state == this->closed[i]->state)
        {
            return; // duplate state in closed list
        }
    }

    for (Node* aNode : this->open.getNodes())
    {
        // TODO: could just add child to open list even if their is a duplicate
        //       then skip expanding it since a duplicate would be guaranteed in the closed list.
        //       Might be more efficient, but not 100% sure, just something to look into, later.

        if (child.state == aNode->state)
        {
            return; // duplate state in open list
        }
    }

    // Add child to open list
    this->open.push(new Node(child));
}