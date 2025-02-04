#include <vector>
#include <queue>
#include <iostream>

#include "Grid.h"

struct GridCell
{
    unsigned int row;
    unsigned int col;
};

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

std::vector<GridCell> search(GridCell start, GridCell end);

// std::vector<GridCell> searchBFS(GridCell start, GridCell end, const Grid& grid);

class SearchAI
{
private:
    std::vector<Node*> closed;
    std::queue<Node*> open;
    // std::vector<Node*> openAndClosed; // TODO?
    // unsigned int nextNode = 0;
    GridCell start;
    GridCell end;
    Grid* grid;
    bool foundGoal = false;

public:

    SearchAI() {}

    void init(GridCell start, GridCell end, Grid* grid);
    void step();

    std::vector<GridCell> getOpen();
    std::vector<GridCell> getClosed();
};