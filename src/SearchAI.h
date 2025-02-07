#include <vector>
#include <queue>
#include <iostream>
#include <stack>
#include <limits>

#include "Grid.h"

struct Node
{
    GridCell state;
    Node* parent;
    unsigned int depth;
};

enum Action
{
    // up is -y, right is +x
    UP, DOWN, LEFT, RIGHT
};

enum SearchAIType
{
    DFS, BFS, ID_DFS
};

std::vector<GridCell> searchDumb(GridCell start, GridCell end);

class StackOrQueue
{
public:
    StackOrQueue();
    StackOrQueue(bool isStack);

    Node* pop();
    void push(Node* node);
    std::vector<GridCell> getGridCells();
    bool isEmpty() const;
    unsigned int size();
    std::vector<Node*> getNodes();

private:
    std::queue<Node*> queue;
    std::stack<Node*> stack;
    bool isStack;
};

class SearchAI
{
private:
    std::vector<Node*> closed;
    StackOrQueue open;
    GridCell start;
    GridCell end;
    Grid* grid;
    Node* goal = nullptr;
    bool foundGoal = false;
    SearchAIType ai;
    const unsigned int MAX_DEPTH = std::numeric_limits<unsigned int>::max();
    unsigned int CUR_MAX_DEPTH = 0;

public:

    SearchAI() {}

    void init(GridCell start, GridCell end, Grid* grid, SearchAIType ai);
    void step();

    std::vector<GridCell> getOpen();
    std::vector<GridCell> getClosed();
    std::vector<GridCell> getSolution();
    bool done();
};
