class Grid
{
public:
    Grid(unsigned int numberOfRows, unsigned int numberOfColumns);
    ~Grid();

    unsigned int get(unsigned int i, unsigned int j);
    void set(unsigned int i, unsigned int j, unsigned int newValue);

private:
    unsigned int** grid;
};