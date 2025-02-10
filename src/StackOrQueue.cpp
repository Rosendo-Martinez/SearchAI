#include "StackOrQueue.h"

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

std::vector<Node*> StackOrQueue::getNodes()
{
    // Make copy of stack/queue
    std::vector<Node*> copy;
    while (!this->isEmpty())
    {
        copy.push_back(this->pop());
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

    return copy;
}