#include <vector>
#include <queue>
#include <iostream>
#include <stack>

#include "Grid.h"

struct Node
{
    GridCell state;
    Node* parent;
};

enum Action
{
    // up is -y, right is +x
    UP, DOWN, LEFT, RIGHT
};

std::vector<GridCell> searchDumb(GridCell start, GridCell end);

class SearchAI
{
private:
    std::vector<Node*> closed;
    std::queue<Node*> open;
    std::stack<Node*> openDFS;
    GridCell start;
    GridCell end;
    Grid* grid;
    Node* goal = nullptr;
    bool foundGoal = false;
    bool usingBFS = true;

public:

    SearchAI() {}

    void init(GridCell start, GridCell end, Grid* grid, bool useBFS = true);
    void step();

    std::vector<GridCell> getOpen();
    std::vector<GridCell> getClosed();
    std::vector<GridCell> getSolution();
    bool done();
};