#include "Grid.h"

/**
 * Does not allocate memory for grid.
 */
Grid::Grid()
{
}

/**
 * Calls createGrid() to create the grid.
 */
Grid::Grid(unsigned int numberOfRows, unsigned int numberOfColumns)
{
    this->changeGrid(numberOfRows, numberOfColumns);
}

Grid::~Grid()
{
    this->free();
}

/**
 * Allocates memory for new grid.
 * Deallocates memory of old grid.
 */
void Grid::changeGrid(unsigned int rows, unsigned int columns)
{
    this->free(); // free old mem.

    // Create 2D array
    this->grid = new unsigned int*[rows];
    for (unsigned int i = 0; i < rows; i++)
    {
        this->grid[i] = new unsigned int[columns];
        // TODO: initialize with default value
    }

    this->rows = rows;
    this->columns = columns;

    this->clear(0); // default value
}

/**
 * Gets the value at row i and column j;
 */
unsigned int Grid::get(unsigned int i, unsigned int j) const
{
    return this->grid[i][j];
}

/**
 * Sets the value at row i and column j;
 */
void Grid::set(unsigned int i, unsigned int j, unsigned int newValue)
{
    this->grid[i][j] = newValue;
}

unsigned int Grid::getNumberOfRows() const
{
    return this->rows;
}

unsigned int Grid::getNumberOfColumns() const
{
    return this->columns;
}

/**
 * Frees memory.
 */
void Grid::free()
{
    if (this->grid != nullptr)
    {
        // free memory
        for (unsigned int i = 0; i < this->rows; i++)
        {
            delete[] this->grid[i];
        }
        delete[] this->grid;
    }
}

/**
 * Clears the grid.
 * All grid cells given the passed in value.
 */
void Grid::clear(unsigned int value)
{
    for (unsigned int i = 0; i < this->getNumberOfRows(); i++)
    {
        for (unsigned int j = 0; j < this->getNumberOfColumns(); j++)
        {
            this->grid[i][j] = value;
        }
    }
}