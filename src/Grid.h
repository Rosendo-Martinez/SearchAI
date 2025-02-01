class Grid
{
public:
    Grid(unsigned int numberOfRows, unsigned int numberOfColumns);
    ~Grid();

    unsigned int get(unsigned int i, unsigned int j) const;
    void set(unsigned int i, unsigned int j, unsigned int newValue);
    unsigned int getNumberOfRows() const;
    unsigned int getNumberOfColumns() const;

private:
    unsigned int** grid;
    unsigned int rows;
    unsigned int columns;
};