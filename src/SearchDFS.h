#include "SearchAI.h"
#include <vector>

struct NodeDFS : public Node
{
    bool SearchedUp = false;
    bool SearchedRight = false;
    bool SearchedDown = false;
    bool SearchedLeft = false;
};

class SearchDFS : public SearchAI
{
public:
    SearchDFS(const Grid* grid, GridCell start, GridCell end);
    ~SearchDFS() override;

    void step() override;
    void finish() override;
    bool done() override;

    const std::vector<Node*> getOpen() override;
    const std::vector<Node*> getClosed() override;
    const std::vector<Node*> getSolution() override;

private:
    GridCell start;
    GridCell end;
    std::vector<NodeDFS*> open; // stack
    const Grid* grid = nullptr;
    bool goal = false;

    void init();
    bool expand(NodeDFS* node, Action act);
};
